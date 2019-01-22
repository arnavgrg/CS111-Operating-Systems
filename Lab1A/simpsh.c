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

//Macros that can be reused throughout the program
#define rd 'r'
#define wr 'w'
#define comm 'c'
#define verb 'v'

//Main function to do all the work
int main(int argc, char* argv[]){

    //Needed for getopt_long
    int choice; 
    int option_index = 0;

    //Set to 1 if --verbose is passed in
    int verbose_flag = 0; 
    //To keep track of current position of index in argv while parsing command
    int command_index = -1;
    
    //Array to keep track of all the file descriptors so far
    int fileds[argc];
    //Variable to keep track of number of fileds in fileds array.
    int numfiles = 0;

    //errorFlag
    int errorFlag = 0;
    int commandErrorFlag = 0;

    //Struct containing flags that can passed through cmd
    static struct option choices[] = {
        {"rdonly",required_argument,NULL,rd},
        {"wronly",required_argument,NULL,wr},
        {"command",required_argument,NULL,comm},
        {"verbose",no_argument,NULL,verb},
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
            //Set curr to the first non-option
            int curr = optind-1;
            while (curr < argc) {
                char* s = argv[curr];
                if (strlen(s) > 2){
                    if (s[0]=='-' && s[1]=='-'){
                        break;
                    }
                }
                fprintf(stdout, " %s", s);
                fflush(stdout);
                curr++;
            }
            fprintf(stdout, "\n");
            fflush(stdout);
        }
        
        //choices[option_index].name has the value of the current flag that was detecte
        //argv[optind] returns the first non option after the detected option
        //if (verbose_flag) {
            //fprintf(stdout, "%s", choices[option_index].name);
        //}
        
        switch (choice) {
            case rd: 
                /*optarg contains argument for the given flag*/
                /*incase of error/failure, optarg is set to null*/
                if (optarg) {
                    //Open file passed in using readonly flag.
                    int fd = open(optarg, O_RDONLY);
                    //If valid file descriptor returned
                    if (fd >= 0){
                        //Add it to the fileds array
                        fileds[numfiles] = fd;
                        //Incremenet number of fileds in array by 1.
                        numfiles += 1;
                    } 
                    //Otherwise write to stderr and exit.
                    else {
                        fprintf(stderr, "Cannot read from file: %d - %s\n", errno, strerror(errno));
                        //Flush stderr
                        fflush(stderr);
                        //Set error flag to 1
                        errorFlag = 1;
                    }     
                }
                break;
            case wr:
                if (optarg) {
                    //Open file passed in using writeonly sflag.
                    int fd = open(optarg, O_WRONLY);
                    //If the returned file descriptor is >= 0
                    if (fd >= 0){
                        fileds[numfiles] = fd;
                        numfiles += 1;
                    } else {
                        //File could not be created/truncated. Print to stderr and exit with status 3.
                        //char buffer[] = "Cannot create or truncate output file:  %d - %s";
                        fprintf(stderr, "Cannot create or truncate output file:  %d - %s\n", errno, strerror(errno));
                        //Flush stderr
                        fflush(stderr);
                        //Set error flag to 1
                        errorFlag = 1;
                    }
                }
                break;
            case verb:
                //If verbose flag is passed in, set verbose_flag to 1. 
                verbose_flag = 1;
                break;
            case comm:
                //find all the parameters passed in after the --command flag
                paramIndex = 0;
                //Go through all the remaining arguments in the argv array
                int curr = optind-1;
                while (curr < argc) {
                    //Set opt to the non-option
                    char* opt = argv[curr];
                    //Make sure opt isn't a flag
                    if (strlen(opt) > 1) {
                        if (opt[0] == '-' && opt[1] == '-'){
                            break;
                        }
                    }
                    //Append opt to options index
                    params[paramIndex] = opt;
                    //Increment index by 1
                    paramIndex++;
                    //Increment optind by 1 to move to the next option in argv
                    curr++;
                }
                //Need to set the last element in params to NULL so 
                //that execvp can be called correctly 
                params[paramIndex] = NULL;
                //Incrememnt paramIndex by 1 (also keeps track of number 
                //of elements in paramIndex)
                paramIndex++;
                
                //Create an integer array of file descriptors used 
                int cfiles [3] = {atoi(params[0]), atoi(params[1]), atoi(params[2])};
                
                //Check if file desctiptors passed in are valid
                //Need to convert the first 3 arguments from strings to numbers
                //so that they can be used as valid file descriptors
                for (int i=0; i < 3; i++) {
                    if ((int)cfiles[i] < 0 || (int)cfiles[i] > numfiles) {
                        fprintf(stderr,"Invalid file descriptor");
                        //Flush stderr after writing to it.
                        fflush(stderr);
                        errorFlag = 1;
                    }
                }
                //Use fork to create a new child process
                pid_t pid = fork();
                //If 0 is returned, it is the child process, otherwise it is 
                //the parent process. If it returns -1, child process creation was unsuccessful.
                if (pid < 0){
                    fprintf(stderr, "Error creating child process", errno, strerror(errno));
                    //Flush stderr after writing to it.
                    fflush(stderr);
                    errorFlag = 1;
                    break;
                }
                if (pid == (pid_t)0) {
                    //Increment file descriptors by 3
                    for (int i=0; i<3; i++) {
                        close(i);
                        dup(fileds[cfiles[i]]);
                        close(fileds[cfiles[i]]);
                    }
                    //Call execvp to run the command in the child process.
                    if ((execvp(params[3], &params[3])) < 0){
                        fprintf(stderr, "Error running command", errno, strerror(errno));
                        //Flush stderr after writing to it.
                        fflush(stderr);
                        errorFlag = 1;
                    }
                }
                break;
            default:
                //Print to stderr and return with status 1.
                fprintf(stderr, "Only valid flags are: --rdonly, --wronly, --verbose and --command\n");
                fflush(stderr);
                errorFlag = 1;
                break;
        }
    }

    //Close all file descriptors after using them.
    for (int i=0; i < numfiles; i++) {
        close(fileds[i]);
    }

    //If no errors, exit with code 0.
    exit(errorFlag);
}