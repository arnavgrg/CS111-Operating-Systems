/*
NAME: Arnav Garg
EMAIL ID: arnavgrg@ucla.edu
UID: 304911796
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
//open and write (to write to .csv)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  

//MACROS
#define THREADS    't'
#define ITERATIONS 'i'
#define YIELD      'y'
#define SYNC       's'

//GLOBALS
//Default values for threads and iterations
static int num_iterations = 1;
static int num_threads = 1;
//Initializing a long long counter to 0
static long long counter = 0;
//Flag to see if --yield flag was passed in
static int opt_yield = 0;
//Flag to see if --sync flag was passed in
static int opt_sync = 0;

//Adder function to demonstrate 
void add(long long *pointer, long long value) {
    long long sum = *pointer + value;
     /*sched_yield() causes the calling thread to relinquish the CPU.  The
       thread is moved to the end of the queue for its static priority and a
       new thread gets to run.*/
    if (opt_yield)
        sched_yield();
    *pointer = sum;
}

//Return difference between start and end time.
long double updateTime(struct timespec s, struct timespec e) {
    //Multiply by 1*10^9 because it is in nanoseconds
    return (( e.tv_sec - s.tv_sec ) * 1000000000 ) + (( e.tv_nsec - s.tv_nsec ));
}

//Function each pthread calls when it is created
void* start_routine() {
    //Add 1 and subtract 1 num_iterations times
    for (int i=0; i<num_iterations; i++) {
        add(&counter, 1);
        add(&counter, -1);
    }
    //Since it needs to return a pointer
    return NULL; 
}

//Main function
int main(int argc, char* argv[]) {
    
    //Initialize/Create variables for getopt_long
    int choice;
    int option_index = 0;

    /* 
        int clock_gettime(clockid_t clk_id, struct timespec *tp);
        struct timespec {
            time_t   tv_sec;        // seconds 
            long     tv_nsec;       // nanoseconds 
        }; 
    */
    //For clock_gettime()
    struct timespec start, end;

    //Struct containing flags that can passed through cli
    static struct option choices[] = {
        {"threads",    optional_argument,  NULL,  THREADS},
        {"iterations", optional_argument,  NULL,  ITERATIONS},
        {"yield",      no_argument,        NULL,  YIELD},
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
                if (optarg){
                    num_threads = atoi(optarg);
                }
                break;
            case ITERATIONS:
                if (optarg) {
                    num_iterations = atoi(optarg);
                }
                break;
            case YIELD:
                opt_yield = 1;
                break;
            default:
                fprintf(stderr, "Only valid options are --threads and --iterations\n");
                fflush(stderr);
                exit(1);
                break;
        }
    }

    //Start clock
    //CLOCK_REALTIME: System-wide clock that measures real (i.e., wall-clock) time.
    if ((clock_gettime(CLOCK_REALTIME, &start)) == -1) {
        fprintf(stderr, "Clock gettime start failed: %d - %s\n", errno, strerror(errno));
        fflush(stderr);
        exit(1);
    }

    //Create an array to store the thread IDs returned while creating num_threads threads.
    pthread_t* threadids = threadids = (pthread_t*)malloc(sizeof(pthread_t) * num_threads);
    
    //Try and malloc. If it fails, exit.
    if (threadids == NULL) {
        fprintf(stderr, "Error allocating memory for threads\n");
        fflush(stderr);
        exit(1);
    }

    /*Thread Creation 
    int pthread_create(pthread_t *restrict thread,
              const pthread_attr_t *restrict attr,
              void *(*start_routine)(void*), void *restrict arg);
        pthread_create arguments:
                1. thread: An opaque, unique identifier for the new thread returned by the subroutine.
                2. attr: An opaque attribute object that may be used to set thread attributes. 
                         You can specify a thread attributes object, or NULL for the default values.
                3. start_routine: the C routine that the thread will execute once it is created.
                4. arg: A single argument that may be passed to start_routine. It must be passed by 
                        reference as a pointer cast of type void. NULL may be used if no argument is to be passed.*/

    //Otherwise, create each thread one by one.
    for (int i=0; i < num_threads; i++){
        //If thread creation fails, write error message, deallocate memory and exit with code 1
        //If thread creation is successful, call start_routine
        if (pthread_create(&threadids[i], NULL, start_routine, NULL) != 0) {
            fprintf(stderr, "Error creating pthreads. Deallocating saved memory.\n");
            fflush(stderr);
            free(threadids);
            exit(1);
        }
    }

    /*Thread joining - wait for thread termination
        int pthread_join(pthread_t thread, void **value_ptr);
        The pthread_join() function shall suspend execution of the calling thread until the 
        target thread terminates, unless the target thread has already terminated. On return 
        from a successful pthread_join() call with a non-NULL value_ptr argument, the value 
        passed to pthread_exit() by the terminating thread shall be made available in the location 
        referenced by value_ptr.*/
    
    for (int i=0; i < num_threads; i++) {
        //If thread joining fails
        if (pthread_join(threadids[i], NULL) != 0){
            fprintf(stderr, "Error joining threads and terminating. Deallocating saved memory");
            fflush(stderr);
            free(threadids);
            exit(1);
        }
    }

    //Stop clock
    //If error, write to stderr and exit with code 1
    if ((clock_gettime(CLOCK_REALTIME, &end)) == -1) {
        fprintf(stderr, "Clock gettime end failed: %d - %s\n", errno, strerror(errno));
        fflush(stderr);
        exit(1);
    }

    //Calculate difference in time and store it in double accum
    long long timing = updateTime(start, end);
    //Calculate total number of operations
    long ops = num_iterations * num_threads * 2;
    //Calculate average time per operation 
    long long avgops = timing/ops;

    /*Prefix add since all test options begin with add 
      and longest option is add-yield-none = 14 characters + '0'*/
    char str[15] = "add";

    //If opt_yield is 1, append -yield to add
    if (opt_yield)
        strcat(str, "-yield");
    //Otherwise, 
    if ((!opt_yield && !opt_sync) || (opt_yield && !opt_sync))
        strcat(str, "-none");

    //Print .csv output line
    /*test name, no. of threads, no. of terations, no. of operations,  
    total runtime, average run time per operation, value of counter*/
    printf("%s,%d,%d,%ld,%lld,%lld,%lld\n", str, num_threads, num_iterations, ops, timing, avgops, counter);

    //Deallocate memory to prevent memory leaks
    free(threadids);

    //Exit with 0 to indicate success.
    exit(0);
}