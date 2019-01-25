/*
NAME: Arnav Garg
EMAIL ID: arnavgrg@ucla.edu
UID: 304911796
*/

//Import libraries 
#include <stdio.h> //printf()
#include <errno.h> //defines the integer variable errno
#include <unistd.h> //getopt_long(), execvp()
#include <getopt.h> //struct for getoptlong
#include <stdlib.h> //exit(), malloc()
#include <fcntl.h> //open() + File access modes used for open() O_RDONLY etc.
#include <sys/types.h> //Needed for open and creat, fork
#include <sys/stat.h> //Needed for open and creat
#include <string.h> //String functions (if needed), atoi
#include <signal.h> //Used to raise/create signals

//Macros that can be reused throughout the program
//Macros for OFlags
#define APPEND      O_APPEND
#define CLOEXEC     O_CLOEXEC
#define CREAT       O_CREAT
#define DIRECTORY   O_DIRECTORY
#define DSYNC       O_DSYNC
#define EXCL        O_EXCL
#define NOFOLLOW    O_NOFOLLOW
#define NONBLOCK    O_NONBLOCK
//Linux implements O_SYNC and O_DSYNC, but not O_RSYNC. (Somewhat
//incorrectly, glibc defines O_RSYNC to have the same value as O_SYNC.)
//#define RSYNC       O_RSYNC
#define SYNC        O_SYNC
#define TRUNC       O_TRUNC
//Macros for file-opening options
#define READ        'l'
#define WRITE       'm'
#define RDWR        'n'
#define PIPE        'o'
//Macros for subcommand options
#define COMMAND     'p'
#define WAIT        'q'
//Macros for miscellaneous options
#define CLOSE       'r'
#define VERBOSE     's'
#define PROFILE     't'
#define ABORT       'u'
#define CATCH       'v'
#define IGNORE      'w'
//DEF instead of DEFAULT to differentiate with default in switch case
#define DEF         'x' 
#define PAUSE       'y'

//Main function to do all the work
int main(int argc, char* argv[]){
    //Needed for getopt_long
    int choice;
    //Set option_index for getopt_long
    int option_index = 0;

    //Set to 1 if --verbose is passed in
    int verbose_flag = 0; 
    
    //Array to keep track of all the file descriptors so far
    int fileds[argc];
    //Variable to keep track of number of fileds in fileds array.
    int numfiles = 0;

    //errorFlag
    int errorFlag = 0;
    //Separate error flag for command
    int commandErrorFlag = 0;

    //flag to keep track of oflags passed in
    int oflags = 0;

    //Struct containing flags that can passed through cmd
    static struct option choices[] = {
        //OFlags
        {"append",      no_argument,        NULL,   APPEND},
        {"cloexec",     no_argument,        NULL,   CLOEXEC},
        {"creat",       no_argument,        NULL,   CREAT},
        {"directory",   no_argument,        NULL,   DIRECTORY},
        {"dsync",       no_argument,        NULL,   DSYNC},
        {"excl",        no_argument,        NULL,   EXCL},
        {"nofollow",    no_argument,        NULL,   NOFOLLOW},
        {"nonblock",    no_argument,        NULL,   NONBLOCK},
        //To deal with glibc's inability to understand O_RSYNC,
        //if rsync is identified, return the same char_flag as sync
        {"rsync",       no_argument,        NULL,   SYNC},
        {"sync",        no_argument,        NULL,   SYNC},
        {"trunc",       no_argument,        NULL,   TRUNC},
        //File-Opening Options
        {"rdonly",      required_argument,  NULL,   READ},
        {"wronly",      required_argument,  NULL,   WRITE},
        {"rdwr",        required_argument,  NULL,   RDWR},
        {"pipe",        no_argument,        NULL,   PIPE},
        //Subcommand Options
        {"command",     required_argument,  NULL,   COMMAND},
        {"wait",        no_argument,        NULL,   WAIT},
        //Miscellaneous Options
        {"close",       required_argument,  NULL,   CLOSE},
        {"verbose",     no_argument,        NULL,   VERBOSE},
        {"profile",     no_argument,        NULL,   PROFILE}, //For Lab1C
        {"abort",       no_argument,        NULL,   ABORT},
        {"catch",       required_argument,  NULL,   CATCH},
        {"ignore",      required_argument,  NULL,   IGNORE},
        {"default",     required_argument,  NULL,   DEF},
        {"pause",       no_argument,        NULL,   PAUSE},
        //Last line needed for the struct to wrok
        {0,0,0,0}
    };

    //Parse command line arguments/flags incrementally
    while ((choice = getopt_long(argc, argv, "", choices, &option_index)) != -1){

        //Non-options array for command flag
        //Automatically get reset each time the while loop is called
        char* params[argc];
        int paramIndex = 0;

        //If verbose flag is turned on, write commands to stdout.
        if (verbose_flag) {
            //Write flag name to output
            fprintf(stdout,"--%s",choices[option_index].name);
            fflush(stdout);
            /* Set curr to the first non-option and save this in a 
            temporary variable to ensure getopt continues from 
            where it left off in the argv array. */
            int curr = optind-1;
            //Keep recursing through argv vector
            while (curr < argc) {
                //Set s to temporary 
                char* s = argv[curr];
                //Stop when the next flag is detected
                if (strlen(s) > 2) {
                    if (s[0]=='-' && s[1]=='-') {
                        break;
                    }
                }
                //Print to stdout
                fprintf(stdout, " %s", s);
                fflush(stdout);
                //Increment optind by 1
                curr++;
            }
            //Print a new line
            fprintf(stdout, "\n");
            fflush(stdout);
        }
        
        //Switch case to detect which flag was detected
        switch (choice) {
            //Perform the same operation for all the open-time flags
            case APPEND:
            case CLOEXEC:
            case CREAT:
            case DIRECTORY:
            case DSYNC:
            case EXCL:
            case NOFOLLOW:
            case NONBLOCK:
            case SYNC:
            case TRUNC:
                /*runtime flags are essentially bitmasks; you create the value 
                by the bitwise OR of the appropriate parameters (using the ‘|’ 
                operator in C)*/
                //After XOR, the value is saved back in oflags
                oflags |= choice;
                break;
            case VERBOSE:
                //If verbose flag is passed in, set verbose_flag to 1. 
                verbose_flag = 1;
                break;
            case READ: 
                /*optarg contains argument for the given flag*/
                /*incase of error/failure, optarg is set to null*/
                if (optarg) {
                    //Open file passed in using readonly flag.
                    int fd = open(optarg, O_RDONLY);
                    //If not a valid file descriptor returned
                    if (fd < 0) {
                        fprintf(stderr, "Cannot read from file: %d - %s\n", errno, strerror(errno));
                        //Flush stderr
                        fflush(stderr);
                        //Set error flag to 1
                        errorFlag = 1;
                        //Append this invalid file descriptor to fileds array
                        fileds[numfiles] = fd;
                        //Incremenet number of file descriptors in array by 1.
                        numfiles += 1;
                    } 
                    //File descriptor is valid.
                    else {
                        //Append valid file descriptor to file descriptor array
                        fileds[numfiles] = fd;
                        //Increment number of fileds in array by 1.
                        numfiles += 1;
                    }
                }
                break;
            case WRITE:
                if (optarg) {
                    //Open file passed in using writeonly sflag.
                    int fd = open(optarg, O_WRONLY);
                    //If the returned file descriptor is invalid
                    if (fd < 0){
                        //File could not be created/truncated. Print to stderr.
                        //char buffer[] = "Cannot create or truncate output file:  %d - %s";
                        fprintf(stderr, "Cannot write to file: %d - %s\n", errno, strerror(errno));
                        //Flush stderr
                        fflush(stderr);
                        //Set error flag to 1
                        errorFlag = 1;
                        //Append invalid file descriptor to fileds array
                        fileds[numfiles] = fd;
                        //Increment number of file descriptors in array by 1
                        numfiles += 1;
                    } 
                    //File descriptor is valid
                    else {
                        //Append valid file descriptor to fileds array
                        fileds[numfiles] = fd;
                        //Increment number of file descriptors in array by 1
                        numfiles += 1;
                    }
                }
                break;
            case RDWR:
                if (optarg) {
                    //Open file passed in using rdwr flag.
                    int fd = open(optarg, O_RDWR);
                    //If the returned file descriptor is invalid
                    if (fd < 0){
                        //File could not be opened for read/write only. Print to stderr.
                        //char buffer[] = "Cannot create or truncate output file:  %d - %s";
                        fprintf(stderr, "Cannot open file for read and write: %d - %s\n", errno, strerror(errno));
                        //Flush stderr
                        fflush(stderr);
                        //Set error flag to 1
                        errorFlag = 1;
                        //Append invalid file descriptor to fileds array
                        fileds[numfiles] = fd;
                        //Increment number of file descriptors in array by 1
                        numfiles += 1;
                    } 
                    //File descriptor is valid
                    else {
                        //Append valid file descriptor to fileds array
                        fileds[numfiles] = fd;
                        //Increment number of file descriptors in array by 1
                        numfiles += 1;
                    }
                }
                break;
            case COMMAND:
                //Reset paramIndex
                paramIndex = 0;
                //Reset commandErrorFlag
                commandErrorFlag = 0;
                //Go through all the remaining arguments in the argv array
                //Decrement optind by 1 so that it starts correctly at the first non-option
                optind--;
                //Go through all the elements in argv from the first non-option detected
                while (optind < argc) {
                    //Set opt to the non-option
                    char* opt = argv[optind];
                    //Make sure opt isn't a flag by checking if the second character is a dash
                    if (strlen(opt) > 1) {
                        if (*(opt+1) == '-'){
                            break;
                        }
                    }
                    //Append opt to options index
                    params[paramIndex] = opt;
                    //Increment index by 1
                    paramIndex++;
                    //Increment optind by 1 to move to the next option in argv
                    optind++;
                }
                //Ensure there are enough arguments for command to work
                if (paramIndex < 4){
                    //Write to stdout
                    fprintf(stderr, "Not enough arguments passed in for --command.");
                    fflush(stderr);
                    //Set flags to 1
                    commandErrorFlag = 1;
                    errorFlag = 1;
                    //Stop execution of command
                    break;
                }
                //Need to set the last element in params to NULL so 
                //that execvp can be called correctly 
                params[paramIndex] = NULL;
                //Incrememnt paramIndex by 1 (also keeps track of number 
                //of elements in paramIndex)
                paramIndex++;
                //Create a set of integers to map to the file descriptors passed in with command
                int input = atoi(params[0]);
                int output = atoi(params[1]);
                int error = atoi(params[2]);
                //Check if file desctiptors passed in are valid
                //Check if input file descriptor is valid
                if (input < 0 || input >= numfiles){
                    //If it is invalid, set commandErrorFlag to 1
                    commandErrorFlag = 1;
                }
                //Check if output file descriptor is valid
                if (output < 0 || output >= numfiles){
                    //If it is invalid, set commandErrorFlag to 1
                    commandErrorFlag = 1;
                }
                //Check if error file descriptor is valid
                if (error < 0 || error >= numfiles){
                    //If it is invalid, set commandErrorFlag to 1
                    commandErrorFlag = 1;
                }
                //If commandErrorFlag is detected, write to stderr.
                if (commandErrorFlag) {
                    //Set errorFlag to 1
                    errorFlag = 1;
                    fprintf(stderr,"Invalid file descriptor\n");
                    //Flush stderr after writing to it.
                    fflush(stderr);
                    //Break out of switch case so that the command cannot be carried out.
                    break;
                }
                //Use fork to create a new child process
                int pid = fork();
                //If 0 is returned, it is the child process, otherwise it is 
                //the parent process. If it returns -1, child process creation was unsuccessful.
                if (pid < 0){
                    fprintf(stderr, "Error creating child process", errno, strerror(errno));
                    //Flush stderr after writing to it.
                    fflush(stderr);
                    //Set commandErrorFlag to 1 to mark detection of error
                    commandErrorFlag = 1;
                    //Break out of switch case and do not continue any further
                    break;
                }
                //Child process
                if (pid == 0) {
                    //Go through each file descriptor one by one, and ensure that
                    //Close stdin, stdout and stderr for the child process, and duplicate 
                    //the file descriptors from the parent file descriptor array.
                    close(0);
                    dup2(fileds[input],0);
                    close(fileds[input]);

                    close(1);
                    dup2(fileds[output],1);
                    close(fileds[output]);

                    close(2);
                    dup2(fileds[error],2);
                    close(fileds[error]);
                    //Call execvp to run the command in the child process, passing in
                    //the command name as the first argument, and its parameters as
                    //as the second argument in execvp
                    if ((execvp(params[3], &params[3])) < 0) {
                        fprintf(stderr, "Error running command", errno, strerror(errno));
                        //Flush stderr after writing to it.
                        fflush(stderr);
                        //Set commandErrorFlag to 1 to highlight that an error was detected
                        commandErrorFlag = 1;
                    }
                }
                break;
            case ABORT:
                ;
                //crash shell by creating a segmentation fault by assigning 
                //a character to a nullptr
                char *s = NULL;
                *s = 'p';
                //signal(SIGABRT, SIG_DFL)
                //abort();
                break;
            default:
                //Print to stderr and return with status 1.
                fprintf(stderr, "Only valid flags are: --rdonly, --wronly, --verbose and --command\n");
                //Flush stderr stream
                fflush(stderr);
                //Set errorFlag to 1 to mark that an error was detected
                errorFlag = 1;
                break;
        }
    }

    //Close all file descriptors in the file descriptor array after using them.
    for (int i=0; i < numfiles; i++) {
        close(fileds[i]);
    }

    //If commandErrorFlag detected, exit with exit(1)
    if (commandErrorFlag){
        exit(commandErrorFlag);
    }
    //Exit with errorFlag
    //If error was found, this exits with 1, else exits with 0
    exit(errorFlag);
}