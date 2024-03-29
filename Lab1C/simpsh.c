/*
NAME: Arnav Garg
EMAIL ID: arnavgrg@ucla.edu
UID: 304911796
*/

/* 
Note: Order of includes/imports matter. I spent over 45 minutes 
trying to determine why my signal handler was not being called,
and why none of my signal system calls were working. I decided
to reorder my includes since I figured maybe there was an issue
with the dependencies of signal or maybe something was overwriting
signal calls/preventing them from happening. This fixed my problem.
*/

//Import libraries 
#include <stdio.h> //printf()
#include <signal.h> //Used to raise/create signals
#include <errno.h> //defines the integer variable errno
#include <sys/resource.h> //for getrusage
#include <unistd.h> //getopt_long(), execvp(), pause(), int pipe()
#include <getopt.h> //struct for getoptlong
#include <stdlib.h> //exit(), malloc()
#include <fcntl.h> //open() + File access modes used for open() O_RDONLY etc.
#include <sys/types.h> //Needed for open and creat, fork
#include <sys/wait.h> //For wait system call
#include <sys/stat.h> //Needed for open and creat
#include <string.h> //String functions (if needed), atoi

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
//Macros for file-opening options  //Bit Mask
#define READ        O_RDONLY       //00
#define WRITE       O_WRONLY       //01
#define RDWR        O_RDWR         //02
#define PIPE        'a'
//Macros for subcommand options
#define COMMAND     'b'
#define WAIT        'c'
//Macros for miscellaneous options
#define CLOSE       'd'
#define VERBOSE     'e'
#define PROFILE     'f'
#define ABORT       'g'
#define CATCH       'h'
#define IGNORE      'i'
//DEF instead of DEFAULT to differentiate with default in switch case
#define DEF         'j' 
#define PAUSE       'k'

//Function definitions
void catch_handler(int num); 
void profileOutput(char* flag, struct rusage usage, double userTime, double systemTime);
void setStartTimes(struct rusage usage, double* startUserTime, double* startSystemTime);
void setEndTimes(struct rusage usage, double* endUserTime, double* endSystemTime);

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
    
    //Array of command_ structs that have PIDs of any child processes 
    //and the execvp command run in the child process
    //struct command_ commandArgs[argc];
    //int commandArgsIndex = 0;

    //Array to store PIDs
    int pids[argc];
    int pidCounter = 0;
    //Array to store commands
    char** commands[argc];
    int commandsCounter = 0;

    //errorFlag
    int errorFlag = 0;
    //Separate error flag for command
    int commandErrorFlag;
    int commandFlag = 0;

    //flag to keep track of oflags passed in
    int oflags = 0;

    //Flag to keep track of wait signal
    int wait_flag  = 0;
    //Max exit and signal numbers
    int maxexitNum = 0;
    int maxSignalNum = 0;
    //Flag to detect if a child terminated with a signal
    int childwithSignal = 0;

    //For waitpid
    int wstatus;
    pid_t childpid;

    //For getrusage
    struct rusage usage; 	
    struct rusage childusage;
	double startUTime, endUTime, UTime;
    double startSTime, endSTime, STime;
    double childStartUTime, childEndUTime, childUTime;
    double childStartSTime, childEndSTime, childSTime;
    int profile_flag = 0;

    //Total time will equal 
    //int ttime = start.ru_utime.tv_sec + start.ru_utime.tv_usec;

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
        {"profile",     no_argument,        NULL,   PROFILE},
        {"abort",       no_argument,        NULL,   ABORT},
        {"catch",       required_argument,  NULL,   CATCH},
        {"ignore",      required_argument,  NULL,   IGNORE},
        {"default",     required_argument,  NULL,   DEF},
        {"pause",       no_argument,        NULL,   PAUSE},
        //Last line needed for the struct to work correctly
        {0,0,0,0}
    };

    //Parse command line arguments/flags incrementally
    while ((choice = getopt_long(argc, argv, "", choices, &option_index)) != -1){

        //Non-options array for command flag
        //Automatically get reset each time the while loop is called
        char* params[argc];
        int paramIndex = 0;
        //File descriptor returned when open system-call used
        int fd = 0;
        //Array for piping
        int pipefds[2]; 
        //Reset paramIndex and commandErrorFlag
        paramIndex = 0;
        commandErrorFlag = 0;
        
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
                        //Break out of while loop to prevent further execution of options
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
        
        //Switch case to see which flag was detected by getopt_long
        switch (choice) {
            case VERBOSE:
                //If verbose flag is passed in, set verbose_flag to 1. 
                verbose_flag = 1;
                break;
            //Perform the same operation for all the open-time flags
            case APPEND:    case CLOEXEC:    case CREAT:
            case DIRECTORY: case DSYNC:      case EXCL:
            case NOFOLLOW:  case NONBLOCK:   case SYNC: 
            case TRUNC:
                /*Open-time flags are essentially bitmasks; you create the value 
                by the bitwise OR of the appropriate parameters (using the ‘|’ 
                operator in C)*/
                //After OR, the value is saved back in oflags
                oflags |= choice;
                break;
            //Deal with rdonly, wronly and rdwr the same way
            case READ:      case WRITE:      case RDWR: 
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1)
                        setStartTimes(usage, &startUTime, &startSTime);
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                /*optarg contains argument for the given flag*/
                /*incase of error/failure, optarg is set to null*/
                //Open file passed in using readonly flag.
                //if (choice == READ || choice == WRITE) {
                  //  fd = open(optarg, choice | oflags);
                //} else {
                    //Provide read and write permissions since it must 
                    //be the O_RDWR flag
                fd = open(optarg, choice | oflags, 0666);
                //}
                //If not a valid file descriptor returned
                if (fd < 0) {
                    fprintf(stderr, "Unable to open file for read or write: %d - %s\n", errno, strerror(errno));
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
                /* Need to reset oflags before next file-opening option is passed in
                since we're done executing all the required open-time flags */
                oflags = 0;
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1){
                        setEndTimes(usage, &endUTime, &endSTime);
                        UTime = endUTime - startUTime;
					    STime = endSTime - startSTime;
                        if (choice == READ)
                            profileOutput("rdonly", usage, UTime, STime);
                        else if (choice == WRITE)
                            profileOutput("wronly", usage, UTime, STime);
                        else
                            profileOutput("rdwr", usage, UTime, STime);
                    }
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                break;
            case COMMAND:
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1)
                        setStartTimes(usage, &startUTime, &startSTime);
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                } 
                //Decrement optind by 1 so that it starts correctly at the first non-option
                optind--;
                //Go through all the elements in argv from the first non-option detected
                while (optind < argc) {
                    //Set opt to the non-option
                    char* opt = argv[optind];
                    //Make sure opt isn't a flag by checking if the second character is a dash
                    if (strlen(opt) > 1) {
                        if (*(opt+1) == '-') {
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
                if (paramIndex < 4) {
                    //Write to stdout
                    fprintf(stderr, "Not enough arguments passed in for --command.");
                    fflush(stderr);
                    //Set flag to 1
                    errorFlag = 1;
                    break;
                }
                //Need to set the last element in params to NULL so 
                //that execvp can be called correctly 
                params[paramIndex] = NULL;
                //Incrememnt paramIndex by 1 (also keeps track of number 
                //of elements in paramIndex)
                paramIndex++;
                //Create a set of integers to map to the file descriptors passed in with command
                int input  = atoi(params[0]);
                int output = atoi(params[1]);
                int error  = atoi(params[2]);
                //Check if file desctiptors passed in are valid
                //Check if input file descriptor is valid
                if (input < 0 || input >= numfiles || fileds[input] < 0)  {
                    //If it is invalid, set commandErrorFlag to 1
                    commandErrorFlag = 1;
                }
                //Check if output file descriptor is valid
                if (output < 0 || output >= numfiles || fileds[input] < 0) {
                    //If it is invalid, set commandErrorFlag to 1
                    commandErrorFlag = 1;
                }
                //Check if error file descriptor is valid
                if (error < 0 || error >= numfiles || fileds[input] < 0) {
                    //If it is invalid, set commandErrorFlag to 1
                    commandErrorFlag = 1;
                }
                //If commandErrorFlag is detected, write to stderr.
                if (commandErrorFlag) {
                    //Set errorFlag to 1
                    errorFlag = 1;
                    fprintf(stderr,"Invalid file descriptors; Files descriptors not within valid range.\n");
                    //Flush stderr after writing to it.
                    fflush(stderr);
                    //Break out of switch case so that the command cannot be carried out.
                    break;
                }
                //Use fork to create a new child process
                int pid = fork();
                //If 0 is returned, it is the child process, otherwise it is 
                //the parent process. If it returns -1, child process creation was unsuccessful.
                if (pid < 0) {
                    fprintf(stderr, "Error creating child process", errno, strerror(errno));
                    //Flush stderr after writing to it.
                    fflush(stderr);
                    //Set commandErrorFlag to 1 to mark detection of error
                    errorFlag = 1;
                    //Break out of switch case and do not continue any further
                    break;
                }
                if (pid == 0) {
                    //Go through each file descriptor one by one, and ensure that that they
                    //can be processed.
                    //Close stdin, stdout and stderr for the child process, and duplicate 
                    //the file descriptors from the parent file descriptor array.
                    //Check to ensure there isn't a -1 in the array
                    //created by the close flag
                    close(0);
                    if (fileds[input] != -1) {
                        dup2(fileds[input],0);
                        //close(fileds[input]);
                    } else {
                        fprintf(stderr, "Invalid file descriptor; File descriptor was closed earlier.");
                        fflush(stderr);
                        errorFlag = 1;
                        break;
                    }
                    close(1);
                    //Check to ensure there isn't a -1 in the array
                    //created by the close flag
                    if (fileds[output] != -1) {
                        dup2(fileds[output],1);
                        //close(fileds[output]);
                    } else if (fileds[output] == -1) {
                        fprintf(stderr, "Invalid file descriptor; File descriptor was closed earlier.");
                        fflush(stderr);
                        errorFlag = 1;
                        break;
                    }
                    close(2);
                    //Check to ensure there isn't a -1 in the array
                    //created by the close flag
                    if (fileds[error] != -1) {
                        dup2(fileds[error],2);
                        //close(fileds[error]);
                    } else {
                        fprintf(stderr, "Invalid file descriptor; File descriptor was closed earlier.");
                        fflush(stderr);
                        errorFlag = 1;
                        break;
                    }
                    //Close all other file descriptors that may be writing to this 
                    //child process so it can begin to read. This is especially true 
                    //in the case of pipe. The read end of any pipe does not start 
                    //until all writes to that pipe are closed.
                    for (int i=0; i<numfiles; i++) {
                        if (fileds[i] != -1 && fileds[i] > 2) {
                            close(fileds[i]);
                        }
                    }
                    //Call execvp to run the command in the child process, passing in
                    //the command name as the first argument, and its parameters as
                    //as the second argument in execvp
                    if ((execvp(params[3], &params[3])) < 0) {
                        fprintf(stderr, "Error running command", errno, strerror(errno));
                        //Flush stderr after writing to it.
                        fflush(stderr);
                        //Set commandErrorFlag to 1 to highlight that an error was detected
                        errorFlag = 1;
                    }
                }
                //Else go into the parent
                if (pid > 0) {
                    //Append child's pid to pid array and increment counter by 1
                    pids[pidCounter] = pid;
                    pidCounter++;
                    //Create enough space to hold the parameters for the execvp command
                    //carried out by the child process
                    char** s = calloc(paramIndex, sizeof(*s));
                    int j = 0;
                    //Go through all the elements in params startin with the command
                    for (int i = 3; i<paramIndex; i++) {
                        //Create memory for the each element in the array
                        s[j] = malloc(sizeof(char*));
                        s[j] = params[i];
                        //Increment the array 
                        j++;
                    }
                    //Finally, add this to the commands array that helps complete
                    //the mapping from PID to EXECVP commands and increment its counter by 1
                    commands[commandsCounter] = s;
                    commandsCounter++;
                }
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1){
                        setEndTimes(usage, &endUTime, &endSTime);
                        UTime = endUTime - startUTime;
					    STime = endSTime - startSTime;
                        profileOutput("command", usage, UTime, STime);
                    }
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                break;
            case CLOSE:
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1)
                        setStartTimes(usage, &startUTime, &startSTime);
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                //Convert string to int
                fd = atoi(optarg);
                //Check if the file descriptor passed in is valid
                if (fd >= numfiles || fd < 0) {
                    fprintf(stderr, "Invalid file descriptor");
                    fflush(stderr);
                    errorFlag = 1;
                    break;
                }
                //If it valid, try closing the file descriptor
                if ((close(fileds[fd])) < 0) {
                    //Write to stderr
                    fprintf(stderr, "Error closing file descriptor");
                    fflush(stderr);
                    errorFlag = 1;
                    break;
                }
                //Set it to -1 to mark that it is closed.
                //This will create errors when the file descriptor 
                //is accessed in the future.
                fileds[fd] = -1;
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1) {
                        setEndTimes(usage, &endUTime, &endSTime);
                        UTime = endUTime - startUTime;
					    STime = endSTime - startSTime;
                        profileOutput("close", usage, UTime, STime);
                    }
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                break;
            case PIPE:
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1)
                        setStartTimes(usage, &startUTime, &startSTime);
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                //Pipe returns -1 on failure, 0 on success
                if (pipe(pipefds) < 0) {
                    fprintf(stderr, "Failure while piping.");
                    fflush(stderr);
                    errorFlag = 1;
                    //Stop execution if failure in piping.
                    break;
                } 
                //Otherwise, pipe succeeded.
                /*The pipe system call finds the first two available positions 
                in the process’s open file table and allocates them for the read 
                and write ends of the pipe. */
                //fd[0] will be the fd for the read end of pipe.
                //fd[1] will be the fd for the write end of pipe.
                //Add both the file descriptors to the file descriptor array
                fileds[numfiles] = pipefds[0]; numfiles++;
                fileds[numfiles] = pipefds[1]; numfiles++;
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1){
                        setEndTimes(usage, &endUTime, &endSTime);
                        UTime = endUTime - startUTime;
					    STime = endSTime - startSTime;
                        profileOutput("pipe", usage, UTime, STime);
                    }
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                break;
            case WAIT:
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1)
                        setStartTimes(usage, &startUTime, &startSTime);
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                //Mark wait flag to true 
                wait_flag = 1;
                //waitpid returns pid of terminated child
                //returns -1 if error
                /*By default, waitpid() waits only for terminated children, 
                but this behavior is modifiable via the options argument */
                /*If wstatus is not NULL, wait() and waitpid() store status 
                information in the int to which it points. wstatus can be 
                inspected by:
                    1. WIFEXITED(wstatus): returns true if the child terminated normally, 
                    that is, by calling exit(3) or _exit(2), or by returning from main().
                    2. WEXITSTATUS(wstatus): returns the exit status of the child. Should
                    only be used if WIFEXITED returns true.
                    3. WIFSIGNALED(wstatus): returns true if the child process was 
                    terminated by a signal.
                    4. WTERMSIG(wstatus): returns the number of the signal that caused the 
                    child process to terminate.  This macro should be employed only if 
                    WIFSIGNALED returned true.*/
                //Initialize wstatus and childpid to 0
                wstatus = 0;
                childpid = 0;
                //waitpid returns the pid of the child that just terminated
                while ((childpid = waitpid(-1, &wstatus, 0)) != -1){
                    //If it is not null, wstatus and childpid were updated
                    //See if child process exited normally
                    if (WIFEXITED(wstatus)) {
                        fprintf(stdout, "exit %d", WEXITSTATUS(wstatus));
                        fflush(stdout);
                        //set maxexitNum to the maximum returned exit code
                        if (WEXITSTATUS(wstatus) > maxexitNum){
                            maxexitNum = WEXITSTATUS(wstatus);
                        }
                        //Print out the corresponding command with all of its 
                        //options
                        for (int i=0; i<pidCounter; i++) {
                            //Find matching pid for pidMap
                            if ((int)childpid == pids[i]) {
                                char** temp = commands[i];
                                for (int j=0; temp[j]!=NULL; j++) {
                                    fprintf(stdout, " %s", temp[j]);
                                    fflush(stdout);
                                }
                            }
                        }
                        fprintf(stdout, "\n");
                        fflush(stdout);
                    } 
                    //If it terminated by a signal, print out signal number 
                    else if (WIFSIGNALED(wstatus)) {
                        //set child with signal to 1 to mark that atleast one 
                        //child terminated with a signal instead of exiting 
                        //normally
                        childwithSignal = 1;
                        fprintf(stdout, "signal %d", WTERMSIG(wstatus));
                        fflush(stdout);
                        //Find the maximum signal number and save this.
                        if (WTERMSIG(wstatus) > maxSignalNum) {
                            maxSignalNum = WTERMSIG(wstatus);
                        }
                        //Print out the corresponding command with all of its 
                        //options
                        for (int i=0; i<pidCounter; i++) {
                            //Find matching pid for pidMap
                            if ((int)childpid == pids[i]) {
                                char** temp = commands[i];
                                for (int j=0; temp[j]!=NULL; j++) {
                                    fprintf(stdout, " %s", temp[j]);
                                    fflush(stdout);
                                }
                            }
                        }
                        fprintf(stdout, "\n");
                        fflush(stdout);
                    }
                }
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1){
                        setEndTimes(usage, &endUTime, &endSTime);
                        UTime = endUTime - startUTime;
					    STime = endSTime - startSTime;
                        profileOutput("wait", usage, UTime, STime);
                    }
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                break;
            case ABORT:
                //Write to stderr and flush stderr stream
                //fprintf(stderr, "Aborting!! Segmentation Violation!!");
                //fflush(stderr);
                //crash shell by raising a segmentation fault signal
                ;
                char *s = NULL;
                *s = 'p';
                break;
            case CATCH:
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1)
                        setStartTimes(usage, &startUTime, &startSTime);
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                //Catch signal passed in
                signal(atoi(optarg), catch_handler);
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1) {
                        setEndTimes(usage, &endUTime, &endSTime);
                        UTime = endUTime - startUTime;
					    STime = endSTime - startSTime;
                        profileOutput("catch", usage, UTime, STime);
                    }
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                break;
            case IGNORE:
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1)
                        setStartTimes(usage, &startUTime, &startSTime);
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                //Ignore signal passed in
                signal(atoi(optarg), SIG_IGN);
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1){
                        setEndTimes(usage, &endUTime, &endSTime);
                        UTime = endUTime - startUTime;
					    STime = endSTime - startSTime;
                        profileOutput("ignore", usage, UTime, STime);
                    }
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                break;
            case DEF:
                /* Handles the signal passed to the program they way it 
                normally would by default */
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1)
                        setStartTimes(usage, &startUTime, &startSTime);
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                signal(atoi(optarg), SIG_DFL);
                if (profile_flag) {
                    if ((getrusage(RUSAGE_SELF, &usage)) != -1) {
                        setEndTimes(usage, &endUTime, &endSTime);
                        UTime = endUTime - startUTime;
					    STime = endSTime - startSTime;
                        profileOutput("default", usage, UTime, STime);
                    }
                    else {
                        fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
                        fflush(stderr);
                    }
                }
                break;
            case PAUSE:
                /*The pause function suspends program execution until a 
                signal arrives whose action is either to execute a handler 
                function, or to terminate the process.*/
                /*If the signal causes a handler function to be executed, 
                then pause returns. This is considered an unsuccessful 
                return (since “successful” behavior would be to suspend 
                the program forever), so the return value is -1. */
                pause();
                break;
            case PROFILE:
                //Set profile flag to 1
                profile_flag = 1;
                break;
            default:
                //Print to stderr and return with status 1.
                fprintf(stderr, "Invalid Flag: Only valid flags are: \n");
                fprintf(stderr, "--rdonly, --wronly, --verbose, --command\n");
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

    //Free memory
    for (int i=0; i<commandsCounter; i++) {
        free(commands[i]);
    }

    //If profile flag and wait flag
    if (profile_flag && wait_flag) {
        if ((getrusage(RUSAGE_CHILDREN, &usage)) != -1) {
            setEndTimes(usage, &endUTime, &endSTime);
            profileOutput("children", usage, endUTime, endSTime);
        }
        else {
            fprintf(stderr, "Getrusage failed: %d - %s", errno, strerror(errno));
            fflush(stderr);
        }
    }

    //If no children terminated with signal, exit with the highest return code it waited for.
    if (wait_flag) {
        //If no child was terminated with a signal, terminate with maximum exit status
        if (!childwithSignal) {
            exit(maxexitNum);
        } 
        //Otherwise, if a child terminated with a signal, 
        else if (childwithSignal) {
            //Reset it to its default disposition
            signal(maxSignalNum,SIG_DFL);
            //Raise the signal so it adds +128 to the max signal number
            raise(maxSignalNum);
        }
    } 

    //Exit with errorFlag
    //If error was found, this exits with 1, else exits with 0
    exit(errorFlag);
}

//Custom catch signal handler
void catch_handler(int num) {
    //Write to stderr with errno.
    fprintf(stderr, "%d caught: %s", num, strerror(num));
    fflush(stderr);
    //Exit with signal number as the status
    exit(num);
}

//Update start time of execution
void setStartTimes(struct rusage usage, double* startUserTime, double* startSystemTime){
    *startUserTime = (double)usage.ru_utime.tv_sec + ((double)usage.ru_utime.tv_usec * 0.000001);
	*startSystemTime = (double)usage.ru_stime.tv_sec + ((double)usage.ru_stime.tv_usec * 0.000001);
}

//Update end time of execution
void setEndTimes(struct rusage usage, double* endUserTime, double* endSystemTime){
    *endUserTime = (double)usage.ru_utime.tv_sec + ((double)usage.ru_utime.tv_usec * 0.000001);
	*endSystemTime = (double)usage.ru_stime.tv_sec + ((double)usage.ru_stime.tv_usec * 0.000001);
}

//Output all options for profile for the given flag
void profileOutput(char* flag, struct rusage usage, double userTime, double systemTime){
    fprintf(stdout, "%s - Time: (user) %fs | (system) %fs\n", flag, userTime, systemTime);
    fflush(stdout);
    /*
    fprintf(stdout, "\tUsage: (system) %fs\n", systemTime);
    fprintf(stdout, "\tMax resident set size: %ld\n", usage.ru_maxrss);
    fprintf(stdout, "\tPage reclaims: %ld\n", usage.ru_minflt);
    fprintf(stdout, "\tPage faults: %ld\n", usage.ru_majflt);
    fprintf(stdout, "\tBlock input operations: %ld\n", usage.ru_inblock);
    fprintf(stdout, "\tBlock output operations: %ld\n", usage.ru_oublock);
    fprintf(stdout, "\tVoluntary context swsitches: %ld\n", usage.ru_nvcsw);
    fprintf(stdout, "\tInvoluntary context switches: %ld\n", usage.ru_nivcsw);
    fflush(stdout);
    */
}