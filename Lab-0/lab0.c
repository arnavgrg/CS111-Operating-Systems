/*
Name: Arnav Garg
Email: arnavgrg@ucla.edu
UID: 304911796
*/

//Import libraries 
#include <stdio.h> //printf()
#include <errno.h> //defines the integer variable errno
#include <unistd.h> //getopt_long()
#include <getopt.h> //struct for getoptlong
#include <stdlib.h> //exit()
#include <signal.h> //signal() + SIGSEGV
#include <fcntl.h> //open() + File access modes used for open() O_RDONLY etc.
#include <sys/types.h> //Needed for open and creat
#include <sys/stat.h> //Needed for open and creat
#include <string.h> //String functions (if needed)

//Macros that can be reused throughout the program
#define input 'i'
#define output 'o'
#define segf 's'
#define catch 'c'
#define dump 'd'

//Function definitions
void createSegfault();  
void segfault_handler(int num);
void incorrectOptions();
void dumpCore();

//Main function to do all the work (taking input, parsing, error checks and producing output)
int main(int argc, char* argv[]){
    //0: stdin
    //1: stdout
    //2: stderr

    //Creating constant array of type struct option
    //More info: http://man7.org/linux/man-pages/man3/getopt.3.html
    /*struct option {
            const char *name;
            int         has_arg;
            int        *flag;
            int         val;
    };
    Last row of array must be filled with 0s
    -> If flag is a null pointer, then the val is a value which identifies this option.
        - If flag is NULL, then getopt_long() returns val.
    -> If flag is not a null pointer, it should be the address of an int 
        variable which is the flag for this option. */
        // 0: no_argument
        // 1: required_argument
        // 2: optional_argument
    static struct option choices[] = {
        {"input",1,NULL,input},
        {"output",1,NULL,output},
        {"segfault",0,NULL,segf},
        {"catch",0,NULL,catch},
        {"dump-core",0,NULL,dump},
        {0,0,0,0}
    };

    //Variables to keep track of:
    int catch_flag = 0;
    int choice, outfile_fd, infile_fd;

    //int getopt(int argc, char *const argv[], const char *optstring)
    /*int getopt_long(int argc, char * const argv[], const char *optstring, 
                        const struct option *longopts, int *longindex);*/
    //More info: http://man7.org/linux/man-pages/man3/getopt.3.html
    /*getopt_long works as follows:
        1. If no options, returns -1 and skips while loop.
        2. If options, checks if all flags are valid. If yes, then
        3. Processes each flag in order from left to right
    */
    while ((choice = getopt_long(argc,argv,"",choices,NULL)) != -1){
        /*Set flags and options correctly so they can be used after the while
        loop*/
        switch (choice){
            case input: 
                /*optarg contains argument for the given flag*/
                /*incase of error/failure, optarg is set to null*/
                if (optarg) {
                    infile_fd = open(optarg, O_RDONLY);
                    /* 
                    Spec: File Descriptor Management
                    int ifd = open(newfile, O_RDONLY);
                    if (ifd >= 0) {
	                    close(0);
	                    dup(ifd);
	                    close(ifd);
                    }
                    */
                    if (infile_fd >= 0){
                        //Close stdin and destroy its file table entry
                        close(0);
                        //Set infile file_descriptor to 0 (stdin)
                        dup2(infile_fd,0);
                        //Close infile_fd
                        close(infile_fd);
                    } 
                    else {
                        /*If no file found, print to stderr and exit with status 2*/
                        /*errno is set by system calls and some library functions in the event 
                        of an error to indicate what went wrong. Don't explicitly define it. */
                        /*sterror returns a pointer to a string that describes
                        the error code passed in the argument*/
                        //Else, infile_fd == -1 which indicates an error while opening the file
                        fprintf(stderr, "Cannot open input file: %d - %s\n", errno, strerror(errno));
				        exit(2);
                    }     
                }
                break;
            case output:
                if (optarg) {
                    // Check if file exists and create the file specified 
                    // if file exists, it is automatically truncated
                    // Set permissions for the file created to rw-
                    // creat is the same as open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    outfile_fd = creat(optarg, 0666);
                    /* 
                    Spec: File Descriptor Management
                    int ofd = creat(newfile, 0666);
                    if (ofd >= 0) {
	                    close(1);
	                    dup(ofd);
	                    close(ofd);
                    }
                    */
                    //If the returned file descriptor is >= 0
                    if (outfile_fd >= 0){
                        //Close stdout and destroy its file table entry
                        close(1);
                        //Set outfile's fd to 1 (stdout) + silently close 
                        dup2(outfile_fd, 1);
                        //Close outfile_fd
                        close(outfile_fd);
                    } else {
                        //File could not be created/truncated. Print to stderr and exit with status 3.
                        fprintf(stderr, "Cannot create or truncate output file:  %d - %s\n", errno, strerror(errno));
                        exit(3);
                    }
                }
                break;
            case segf:
                //Call the createSegfault() method to immediately cause a segfault.
                createSegfault();
                break;
            case catch:
                //Set catch_flag to 1 (for dump case)
                catch_flag = 1;
                /* If a segfault is called after this line, instead of breaking out of the
                program or going into an infinity loop (depending on the OS), it calls 
                the segfault_handler method to handle the segmentation fault */
                signal(SIGSEGV, segfault_handler);
                break;
            case dump:
                /*If dump-core is passed in by itself, do nothing
                If segfault is passed in before dump-core, doesn't matter
                If catch is passed in before dump-core, call dumpCore method.*/
                if (catch_flag){dumpCore();}
                break;
            default:
                //If wrong/unrecognized flag is passed in, call the icorrectOptions method
                incorrectOptions();
                break;
        }
    }

    /* If no options are passed, need to take input from stdin and
    print it out to stdout */
    char buffer[1];
    size_t r, w;
    //0 marks end of file
    //Read one byte of data from stdin
    while ((r = read(0,buffer,sizeof(char))) > 0) {
        //Check for read-in errorr or signal interrupt
        if (r == (size_t)-1) {
            fprintf(stderr, "Error reading from file/stdout: %s\n", strerror(errno));
            exit(5);
        }
        //Write one byte to stdout
        w = write(1,buffer,sizeof(char));
        //Check if write system call fails and print to stderr
        if ((int)w < 0){
            fprintf(stderr, "Unable to write to stdout: %d - %s\n", errno, strerror(errno));
            exit(6);
        } 
        //Number of bytes read should equal number of bytes written
        else if (w != r) {
            fprintf(stderr,"Number of bytes read from stdin does not equal number of bytes written to stdout. \
                        Bytes read: %d; Bytes written: %d\n",(int)r,(int)w);
            exit(7);
        }
    }

    //Close stdin and stdout after using them.
    //This destroys the file table entry referenced to by each element
    close(0);
    close(1);

    /*If no errors, exit with code 0 to indicate successful copy 
    from stdin to stdout*/
    exit(0);
}

/*Create segfault by assigning value to a nullptr without
allocating memory to store this value */
void createSegfault() {
    char* p = NULL;
    //Segfault created in this line of code
    *p = 'S';
    return;
    //By default, exits with status code 139
}

//Print to stderr and exit if segfault is caught
void segfault_handler(int num) {
    if (num == SIGSEGV){
        fprintf(stderr, "SIGSEGV signal caught: error number: %d; message: %s\n", errno, strerror(errno));
        exit(4);
    }
}

//dumpCore method
void dumpCore() {
    /*reset signal for segmentation fault to default 
    instead of calling segfault_handler and exit with status 139*/
    signal(SIGSEGV, SIG_DFL);
}

//If wrong flag/option is passed into the program
void incorrectOptions() {
    fprintf(stderr, "Only valid options are --input=filename, --output=filename, --catch, --segfault and --dump-core\n");
    exit(1);
}