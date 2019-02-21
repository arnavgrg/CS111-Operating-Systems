/*
NAME: ARNAV GARG
UID: 304911796
EMAIL: arnavgrg@ucla.edu
SLIPDAYS: 0
*/

//LIBRARIES
//fprintf, printf, sprintf etc
#include <stdio.h> 
//getopt_long()
#include <unistd.h> 
//struct for getoptlong
#include <getopt.h> 
//exit(), malloc()
#include <stdlib.h> 
//defines the integer variable errno
#include <errno.h> 
//clock_gettime()
#include <time.h>
//strerror, strcat
#include <string.h>
//create, detach, join threads
#include <pthread.h>
//Sched_yield()
#include <sched.h>
//Include header for SortedList
#include "SortedList.h"

#include "gperftools/profiler.h"

//MACROS
#define THREADS    't'
#define ITERATIONS 'i'
#define YIELD      'y'
#define SYNC       'l'
#define MUTEX      'm'
#define SPINLOCK   's'
#define LISTS      'x'

/*YIELD BASED MACROS
#define	INSERT_YIELD	0x01
#define	DELETE_YIELD	0x02
#define	LOOKUP_YIELD	0x04
ID_YIELD - Or 0x01 with 0x02
IL_YIELD - Or 0x01 with 0x04
DL_YIELD - Or 0x02 with 0x04
IDL_YIELD - Or 0x01 with 0x02 and with 0x04
This works because they are bit masks, so we can just or them like we
did with the runtime open flags in Lab1ABC.
*/
#define ID_YIELD   0x03  
#define IL_YIELD   0x05  
#define DL_YIELD   0x06  
#define IDL_YIELD  0x07

//Set opt yield to 0 (so external int in SortedList.h can pick up on it)
int opt_yield = 0;

//Fixing the size of the key length 
const int KEYLEN = 5;

//Create a struct that represents each sublist
/*Every sublist should contain its own list + elements, and a way to turn on/set sync 
options if they are passed in*/
typedef struct {
    SortedList_t list;
    int s_lock;
    pthread_mutex_t m_lock;
} sublist;

//GLOBALS
//Default values for threads and iterations
static int num_lists = 1;
static int num_iterations = 1;
static int num_threads = 1;
//For sync
static int sync_flag = 0;
static int sync_m = 0;
static int sync_s = 0;
//Static variable to use pthread_mutex
static pthread_mutex_t x;
//Static variable for spinlock
static int splock = 0;

//Total number of elements to be created in the list
static int num_elements = 0;
/*Create an array of elements for this list*/
static SortedListElement_t *array_elements = NULL;
//Start position for each of the threads
static int *start_position = NULL;
//Create an array of sublists
static sublist *sublists = NULL;
//Create an array to save the wait times for each of the threads
//Needed to analyze the total lock acquisition time
static long long *thread_wait_times = NULL;
//Create an array to store the thread IDs returned while creating num_threads threads.
static pthread_t* threadids = NULL;

//djb2 Hash function that hashes a string
//Picked this hash function because it was mentioned on Piazza and seemed 
//the easiest to use
//Link: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str){
    unsigned long hash = 5381;
    for (int i=0; i < KEYLEN; i++)
        hash = ((hash << 5) + hash) + str[i];
    return hash;
}

//Jenkin's One at a time Hash function
//Link: https://en.wikibooks.org/wiki/Algorithm_Implementation/Hashing
unsigned long hash2(const char* str) {
    unsigned long hash_val = 0;
    for (int i = 0; i < KEYLEN; i++) {
        hash_val += str[i];
        hash_val += (hash_val << 10);
        hash_val ^= (hash_val >> 6);
    }
    hash_val += (hash_val << 3);
    hash_val ^= (hash_val >> 11);
    hash_val += (hash_val << 15);
    return hash_val;
}

//Flush stderr, free memory and exit with status 1
void exit_1() {
    fflush(stderr);
    freeMemory();
    exit(1);
}

//Flush stderr, free memory and exit with status 2
void exit_2() {
    fflush(stderr);
    freeMemory();
    exit(2);
}

//Free all malloc'd memory incase of failure, or before exiting
void freeMemory() {
    free(array_elements);
    free(start_position);
    free(sublists);
    free(threadids);
    free(thread_wait_times);
}

//Initialize memory for lists
void initializeMemoryForLists() {
    sublists =  malloc(sizeof(sublist) * num_lists);
    //If malloc failed, write to stderr and exit with status 2
    if (!sublists) {
        fprintf(stderr, "Malloc failed when trying to allocate memory for lists\n");
        exit_2();
    }
}

//Function to initialize each of the empty sublists
void initializeSublists() {
    //For each of the given lists
    for (int i=0; i < num_lists; i++) {
        //Create an instance of the struct and initialize 
        //it to the given memory space in the lists array
        sublist *s = &sublists[i];
        //Initialize the list in the struct
        //This is the same as creating a head node for the sublist
        SortedList_t *l = &s->list;
        l->key = NULL;
        l->next = l;
        l->prev = l;
        //Check if spinlock option was passed in for sync flag and
        //initialize a value for the spinlock member in the struct
        if (sync_s)
            s->s_lock = 0;
        //Check if mutex option was passed in for sync flag
        else if (sync_m) {
            //Initialize a mutex lock for the thread
            //Incase of failure, write to stderr, free memory and exit with status 1
            if (!pthread_mutex_init(&s->m_lock, NULL)) {
                fprintf(stderr, "Failure initializing mutex lock for thread\n");
                exit_1();
            }
        }
    }
}

//Function to create enough space for required elements and initialize
//each elements key using a pseudorandom string key.
void createElements() {
    //Calculate the required number of elements and create 
    //enough memory to store the required elements
    num_elements = num_iterations * num_threads;
    array_elements = malloc(sizeof(SortedListElement_t) * num_elements);
    //Check if malloc fails and report error and exit status correctly
    if (!array_elements) {
        fprintf(stderr, "Malloc failed\n");
        exit_1();
    }
    //Need to initialize each element with a key
    /*Set a unique seed everytime srand is called to generate a new
    set of pseudo-random numbers. Only need to do this once before using it*/
    srand((unsigned int) time(NULL));
    //Go through all the required elements in the linked list
    for (int i=0; i < num_elements; i++) {
        //Allocate memory for a new key of size KEYLEN
        char* new_key = malloc(sizeof(char *) * (KEYLEN+1));
        //Set the key
        for (int j=0; j<KEYLEN; j++) {
            new_key[j] = (char) rand() % 26 + 'A';
        }
        //Adding a null byte at the end 
        new_key[KEYLEN] = '\0';
        //Add this key in the array_elements array
        array_elements[i].key = new_key;
    }
}

//Function to create enough memory and initialize wait times for each of the 
//threads to 0.
void initializeWaitTimes() {
    //Allocate enough memory to store wait times for each of the threads during locks
    thread_wait_times = malloc(sizeof(long long) * num_threads);
    if (!thread_wait_times) {
        fprintf(stderr, "Failure while create memory for starting positions\n");
        exit_1();
    }
    //If malloc was successful, initialize the wait times for each of the threads to 0
    for (int i=0; i < num_threads; i++) {
        thread_wait_times[i] = 0;
    }
}

//Initialize sublists with the elements
void initialize() {
    //Allocate enough memory to hold the required number of sublists
    initializeMemoryForLists();
    //Initialize each of the empty sublists
    initializeSublists();
    //Create elements and initialize each element's key
    createElements();
    //Initialize wait times for each of the threads
    initializeWaitTimes();
    //Allocate enough memory to hold the starting position for each thread.
    start_position = malloc(sizeof(int) * num_threads);
    if (!start_position) {
        fprintf(stderr, "Failure while create memory for starting positions\n");
        exit_1();
    }
}

//Helper function to search and delete elements from a given list
void validateDelete(SortedList_t *list, const char *str) {
    //Lookup element element with key str in given list
    SortedListElement_t *t = SortedList_lookup(list,str);
    //If t is a nullptr, element wasn't found so write to stderr and exit
    if (t == NULL) {
        fprintf(stderr, "Element not found in list\n");
        exit_2();
    } 
    //If SortedList_delete returns 1, delete failed so write to stderr and exit
    if (SortedList_delete(t)) {
        fprintf(stderr, "Failed to delete element successfully\n");
        exit_2();
    }
}

void* start_routine(void* val) {
    //Set the bounds for each thread so that work doesn't overlap
    int start_pos = *((int *) val);
    int end_pos = start_pos + num_iterations;

    //Insert elements
    for (int i=start_pos; i<end_pos; i++) {
        //If mutex flag is 1
        if (sync_m){
            pthread_mutex_lock(&x);
            SortedList_insert(&list, &array_elements[i]);
            pthread_mutex_unlock(&x);
        } 
        //If spinlock flag
        else if (sync_s){
            while (__sync_lock_test_and_set(&splock, 1));
            //Inside Critical Section
            SortedList_insert(&list, &array_elements[i]);
            __sync_lock_release(&splock);
        } 
        //No sync flags were passed
        else
            SortedList_insert(&list, &array_elements[i]);
    }

    //Find the length of the list
    int length = 0;
    if (sync_m){
        pthread_mutex_lock(&x);
        length = SortedList_length(&list);
        pthread_mutex_unlock(&x);
    } else if (sync_s){
        while (__sync_lock_test_and_set(&splock, 1));
        //Inside Critical Section
        length = SortedList_length(&list);
        __sync_lock_release(&splock);
    } else 
        length = SortedList_length(&list);
    //If this value is 0, no elements were inserted
    if (length <= 0) {
        fprintf(stderr, "List is corrupted\n");
        exit_2();
    }

    //Delete each of the keys
    for (int i=start_pos; i<end_pos; i++) {
        if (sync_m){
            pthread_mutex_lock(&x);
            validateDelete(i);
            pthread_mutex_unlock(&x);
        } else if (sync_s) {
            while (__sync_lock_test_and_set(&splock, 1));
            //Inside critical section
            validateDelete(i);
            __sync_lock_release(&splock);
        } else 
            //Helper method deletes the element as well
            validateDelete(i);
    }

    //Need to return null since the function needs to return a pointer
    return NULL;
}

//Return difference between start and end time.
long double updateTime(struct timespec s, struct timespec e) {
    //Multiply by 1*10^9 because it is in nanoseconds
    return (( e.tv_sec - s.tv_sec ) * 1000000000 ) + (( e.tv_nsec - s.tv_nsec ));
}

int main(int argc, char* argv[]) {
    //Initialize/Create variables for getopt_long
    int choice;
    int option_index = 0;
    //For clock_gettime()
    struct timespec start, end;

    //Struct containing flags that can passed through cli
    static struct option choices[] = {
        {"threads",    optional_argument,  NULL,  THREADS},
        {"iterations", optional_argument,  NULL,  ITERATIONS},
        {"yield",      required_argument,  NULL,  YIELD},
        {"sync",       required_argument,  NULL,  SYNC},
        {"lists",      required_argument,  NULL,  LISTS},
        //Last line needed for the struct to work correctly
        {0,0,0,0}
    };

    //While loop to go through all the options that were passed in during runtime
    /*Since argument is optional for threads and iterations if an argument was passed 
    in, it is saved in optarg. In this case, update num_threads and num_iterations to 
    their corresponding values. Otherwise, optarg is null and num_threads/num_iterations. 
    remain at their default value of 1.*/
    while ((choice = getopt_long(argc, argv, "", choices, &option_index)) != -1) {
        switch (choice) {
            case THREADS:
                //Update num_threads if an argument was passed in
                if (optarg)
                    num_threads = atoi(optarg);
                break;
            case ITERATIONS:
                //Update num_iterations if an argument was passed in
                if (optarg) 
                    num_iterations = atoi(optarg);
                break;
            case LISTS:
                //Update num_lists if a argument was passed in
                if (optarg)
                    num_lists = atoi(optarg);
                break;
            case YIELD: ;
                //can take [idl] where i is insert, d is delete and l is lookup
                //Find length 
                size_t len = strlen(optarg);
                //Too many arguments
                if (len > (size_t)3 || len <= (size_t)0){   
                    fprintf(stderr, "Too many/few arguments for --yield flag\n");
                    exit_2();
                }
                //Process argument
                for (int i=0; i < (int)len; i++) {
                    if (optarg[i] == 'i')
                        opt_yield |= INSERT_YIELD;
                    else if (optarg[i] == 'd')
                        opt_yield |= DELETE_YIELD;
                    else if (optarg[i] == 'l')
                        opt_yield |= LOOKUP_YIELD;
                    else {
                        fprintf(stderr, "Invalid argument(s) for --yield flag\n");
                        exit_2();
                    }
                }
                break;
            case SYNC:
                //Set sync flag to 1
                sync_flag = 1;
                //Get first argument
                int opt_sync = optarg[0];
                //Check if it is one of the valid arguments
                //Need to write it like this because of DeMorgan's Rule
                if ((opt_sync != SPINLOCK) && (opt_sync != MUTEX)){
                    fprintf(stderr, "Invalid arguments for --sync flag\n");
                    exit_2();
                }
                //If mutex is passed in, set flag to 1
                if (opt_sync == MUTEX)
                    sync_m = 1;
                //Else the option must be spinlock, so initialize its flag to 1
                else 
                    sync_s = 1;
                break;
            default:
                fprintf(stderr, "Invalid Arguments passed in.\n");
                exit_1();
                break;
        }
    }

    /*Call the initialize function to initialize a linked list with
    the iterations*thread elements, each with a unique key*/
    initialize();

    //Create an array to store the thread IDs returned while creating num_threads threads.
    threadids = (pthread_t*)malloc(sizeof(pthread_t) * num_threads);
    
    //Try and malloc. If it fails, deallocate memory and exit.
    if (!threadids) {
        fprintf(stderr, "Error allocating memory for threads\n");
        exit_1();
    }

    //Start clock
    if ((clock_gettime(CLOCK_MONOTONIC, &start)) == -1) {
        fprintf(stderr, "Clock gettime start failed: %d - %s\n", errno, strerror(errno));
        exit_1();
    }

    //Otherwise, create each thread one by one.
    for (int i=0, pos=0; i < num_threads; i++, pos += num_iterations) {
        //If thread creation fails, write error message, deallocate memory and exit with code 1
        //If thread creation is successful, call start_routine
        //Note down start position for each of the threads so they don't conflict/overlap
        start_position[i] = pos;
        if (pthread_create(&threadids[i], NULL, start_routine, (void*) &start_position[i]) != 0) {
            fprintf(stderr, "Error creating pthreads. Deallocating saved memory.\n");
            exit_1();
        }
    }

    //Join each of the threads after they're done executing
    for (int i=0; i < num_threads; i++) {
        //If thread joining fails 
        if (pthread_join(threadids[i], NULL) != 0) {
            fprintf(stderr, "Error joining threads and terminating. Deallocating saved memory\n");
            exit_1();
        }
    }

    //Stop clock
    //If error, write to stderr and exit with code 1
    if ((clock_gettime(CLOCK_MONOTONIC, &end)) == -1) {
        fprintf(stderr, "Clock gettime end failed: %d - %s\n", errno, strerror(errno));
        exit_1();
    }

    //Check if length of the list is actually 0 
    if (SortedList_length(&list) != 0){
        fprintf(stderr, "Length is not 0\n");
        exit_2();
    }

    //Create a 16 character list to store option
    char str[16] = "list";
    
    //See if opt_yield was changed (it will be if --yield was passed in)
    switch(opt_yield) {
        case INSERT_YIELD:    strcat(str, "-i");         break;
        case DELETE_YIELD:    strcat(str, "-d");         break;
        case LOOKUP_YIELD:    strcat(str, "-l");         break;
        case DL_YIELD:        strcat(str, "-dl");        break;
        case IL_YIELD:        strcat(str, "-il");        break;
        case ID_YIELD:        strcat(str, "-id");        break;
        case IDL_YIELD:       strcat(str, "-idl");       break;
        default:              strcat(str, "-none");      break;
    }

    //If sync flag was passed in, see if we need to append mutex or spinlock
    if (sync_flag) {
        if (sync_m)
            strcat(str, "-m");
        else 
            strcat(str, "-s");
    }   else 
            strcat(str, "-none");

    //Calculate difference in time and store it in double accum
    long long timing = updateTime(start, end);
    //Calculate total number of operations
    long long ops = num_threads*num_iterations*3;
    //Calculate average time per operation
    long long avgops = timing/ops;

    //Print .csv output line
    /*test name, no. of threads, no. of terations, no. of lists, 
    no. of operations, total runtime, average run time per operation*/
    printf("%s,%d,%d,%d,%lld,%lld,%lld\n", str, num_threads, num_iterations, num_lists, ops, timing, avgops);

    //Free Memory
    freeMemory();

    //Exit successfully so return 0
    exit(0);
}