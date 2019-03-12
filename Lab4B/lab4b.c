//NAME: Arnav Garg
//ID: 304911796
//EMAIL: arnavgrg@ucla.edu

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <mraa.h>
#include <aio.h>
#include <getopt.h>
#include <poll.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include <math.h>
#include <sys/fcntl.h>
#include <limits.h>

#define PERIOD 'p'
#define SCALE  's'
#define LOG    'l'

//Max size of input buffer for user input
const int BUFFER_SIZE = 512;

//Initialize a global static variable called period to 1
static int period = 1;
//Initialize scale to F (default)
static char scale = 'F';
//Set generate (print to stdout) to 1 (true) so it can log by default
static int generate = 1;
//Initialize a FILE variable to NULL, and will eventually point to a valid file stream if the option
//is passed in
FILE* log_file = NULL;
//Keep track of required time before next log entry
time_t next_time = 0;

//Create instances of the Sensor & Button
mraa_aio_context sensor;
mraa_gpio_context button;

//Print errors and exit
void print_error(char* err) {
    fprintf(stderr, "%s\n", err);
    fflush(stderr);
    exit(1);
}

//Print errors with errno
void print_error_with_errno(char* err, int error_num) {
    fprintf(stderr, "%s: %d - %s\n", err, error_num, strerror(error_num));
    fflush(stderr);
    exit(1);
}

//Incorrect arguments/bogus arguments passed into CLI during initial call
void incorrect_arguments(){
	fprintf(stderr, "Invalid argument passed in\n");
    fflush(stderr);
    exit(1);
}

//Helper method to write output to a log file if it is processed
void write_to_log_file(char* str) {
	if (log_file){
		fprintf(log_file, "%s\n", str);
		fflush(log_file);
	}
}

//Close logfile incase it is open
void close_file_and_sensors() {
  	//Check if log_file is pointing to a file stream
  	if (log_file) {
      	if (fclose(log_file)) {
        	print_error("Program failed to close the log file");
      	}
  	}
  	//Close button and sensor
  	mraa_aio_close(sensor);
  	mraa_gpio_close(button);
}

//Convert reading into a temperature, either in C or F
//http://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/
float getTemperature() {
	int a = mraa_aio_read(sensor);
    int B = 4275;
    int R_0 = 100000;
    float R = R_0 * (1023.0/(a-1.0));
    float result = 1.0/(log(R/R_0)/B+1/298.15)-273.15;
    //By default, temperature conversion is in C. So if scale=F, we need to convert
    if (scale == 'F')
		return result*1.8 + 32;
	return result;
}

//Function to get time in the correct format
//For this function to work correctly, we need to configure the local timezone on our BeagleBone.
void getTime() {
    time_t current;
    //This function returns the time since 00:00:00 UTC, January 1, 1970 (Unix timestamp) in seconds.
    time(&current);
    //The time returned from localtime(3) will only be in the correct timezone if you have correctly configured 
    //the local timezone on your embedded system.
    struct tm *localTimeNow = localtime(&current);
    if (!localTimeNow)
        print_error("Failure initializing struct tm");
	//Initialize a string
    char p_time[10];
    /*The strftime() function formats the broken-down time tm according to the format specification format and places 
    the result in the character array s of size max.*/
    //size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);
    strftime(p_time, 9, "%H:%M:%S", localTimeNow);
    //See if a log file was passed in opened correctly
    if (log_file) {
        fprintf(log_file, "%s ", p_time);
        fflush(log_file);
    } 
	//Otherwise, just write to stdout
	else {
        printf("%s ", p_time);
        fflush(stdout);
    }
}

//Create stdout entry and write to stdout/file stream
void log_entry() {
	//Struct to get time of the day
	struct timeval tclock;
	//Get time of the day and save it in tclock
	gettimeofday(&tclock, 0);
	//Only if logging is turned on and the current_time is greater than the next required time
	//Otherwise, we don't write to stdout/logfile
	if (generate && tclock.tv_sec >= next_time) {
		//Print out the timestamp
		getTime();
		//Get time from getTemperature function
		float temperature = getTemperature();
		//If logging is turned on, write to logfile
		if (log_file) {
			fprintf(log_file, "%.1f\n", temperature);
			fflush(stdout);
		} 
		//Otherwise, write to stdout
		else {
			printf("%.1f\n", temperature);
			fflush(stdout);
		}
		//Update next_time to current time + the next period so we only log a 
		//new entry when we hit the next time interval
		next_time = tclock.tv_sec + period;
	}
}

//Logs one final temperature reading and exits
void shutdown() {
  	//If there is a log file, write to the logfile
  	if (log_file) {
    	getTime();
    	write_to_log_file("SHUTDOWN");
    	exit(0);
  	}
  	//Otherwise, write to stdout
  	getTime();
  	printf("SHUTDOWN\n");
  	fflush(stdout);
  	exit(0);
}

//Process user inputs passed in at runtime
void process_inputs(char* input) {
	//Set the last byte in the string to a null byte
	int strlength = strlen(input);
	input[strlength - 1] = '\0';
	//Eliminate possible spaces/tab spaces from user input
	while (*input == ' ')
		input++;
	//If the substring is in the string, then return a pointer to the index in the string
	//where the substring starts
	char* period_ptr = strstr(input, "PERIOD=");
	char* log_ptr = strstr(input, "LOG");
	//Check if the given condition is OFF
	//If yes, then we want to disable logs from being generated, so set this to 0
	if (strcmp(input,"OFF") == 0) {
		write_to_log_file(input);
		//Call shutdown to print final line of output and stop execution of program
		shutdown();
	}
	//Check if the given condition is SCALE=C
	//In this case, we need to udpate the value of our scale variable
	else if (strcmp(input,"SCALE=C") == 0) {
		scale = 'C';
		write_to_log_file(input);
	}
	//Check if the given condition is SCALE=F
	//In this case, we need to update the value of our scale variable
	else if (strcmp(input,"SCALE=F") == 0) {
		scale = 'F';
		write_to_log_file(input);
	}
	//Check if the given condition is STOP
	//If yes, then we want to disable logs from being generated, so set this to 0
	else if (strcmp(input,"STOP") == 0) {
		generate = 0;
		write_to_log_file(input);
	}
	//Check if the given condition is START
	//If yes, then we want to enable logs to be generated, so set this to 1
	else if (strcmp(input,"START") == 0) {
		generate = 1;
		write_to_log_file(input);
	}
	//Check if the given condition is PERIOD=
	//If yes, then we want to find the new period number and set period to this number
	else if (period_ptr) {
		char* index = input;
		index += 7; //PERIOD= <- ptr will point here
		//Check if this is the end of the string (if it is the zero byte)
		//If it is not the end of the file, then get the number
		if (*index) {
			//Convert the remainder of the string from a string to an integer
			int new_period = atoi(index);
			//Go through all the characters in the remainder of the string
			//They must all be digits, otherwise return and do nothing
			while(*index) {
				if (!isdigit(*index))
					return;
				index++;
			}
			//Update period to this new value
			period = new_period;
		}
		//Log entry only if the value passed in for period is correct
		write_to_log_file(input);
	}
	//Check if the given condition is LOG 'line of text'
	//Need to do nothing, just record it
	else if (log_ptr) 
		write_to_log_file(log_ptr);
	//The command is not one we recognise
	//If logging is enabled, all received commands (valid or not) should be appended to the log file (exactly as received, 
	//with no timestamp) but not displayed to standard output. 
	else 
		write_to_log_file(input);
	//Reset to null to prevent dangling pointers problems
	period_ptr = NULL;
	log_ptr = NULL;
}

//Initialize temperature sensor
void initialize_sensor() {
    //Initialise an Analog input device, connected to the specified pin. 
    //Aio pins are always 0 indexed reguardless of their position.
    //Grove Temperature Sensor to the Analog A0/A1 connector on your Grove cape, where it will be addressed as I/O pin #1.
    sensor = mraa_aio_init(1);
    //Check if the sensor failed to initialize
    if (!sensor)
       	print_error_with_errno("Temperature sensor failed to initialize correctly", errno);
}

//Initialize button
void initialize_button() {
    //Initialise gpio_context, based on board number
    //GPIO     MRAA
    //GPIO_51   62
    //GPIO_50   60
    //Grove Button attached to the GPIO_50 connector on Grove cape, where it will be addressed as I/O pin #60.
    button = mraa_gpio_init(60);
    //Check if the button failed to initialize
    if (!button)
      print_error_with_errno("Button failed to initialize correctly", errno);
    //Set button to be input
    mraa_gpio_dir(button, MRAA_GPIO_IN);
    //Setup an event handler for the button that automatically gets triggered if the button is pressed
    //It calls the shutdown function, logging the last line and exiting
    mraa_gpio_isr(button, MRAA_GPIO_EDGE_FALLING, &shutdown, NULL);
}
                     
//Main function
int main(int argc, char* argv[]) {
    //Needed for getopt_long
    int choice;
    //Set option_index for getopt_long
    int option_index = 0;
    
	//Poll struct
    //int poll(struct pollfd *fds, nfds_t nfds, int timeout);
    /* struct pollfd {
               int   fd;         //file descriptor
               short events;     //requested events (input)
               short revents;    //returned events (output)
       };   */
    /* If none of the events requested (and no error) has occurred for any of the file descriptors, then 
    poll() blocks until one of the events occurs.*/
    struct pollfd cmdsPoll;

    //Struct containing choices for getopt
    static struct option choices[] = {
		{"period", optional_argument, NULL, PERIOD},
      	{"scale",  optional_argument, NULL, SCALE},
      	{"log",    required_argument, NULL, LOG},
      	{0,0,0,0}
    };
    
    //Main getopt while loop to process CLI arguments    
    while ((choice = getopt_long(argc, argv, "", choices, &option_index)) != -1) {
        switch(choice) {
        	//Case Period: sampling interval
        	case PERIOD: 
          		if (atoi(optarg) < 0)
            		print_error("Period cannot be a negative value");
          		if (optarg)
            		period = atoi(optarg);    
          		break;
        	//Case to process whether the decided scale is F or C
        	case SCALE: 
          		if (strlen(optarg) > 1)
            		print_error("Too many characters specified for scale");
          		else if (optarg[0] == 'C')
            		scale = 'C';
          		else if (optarg[0] == 'F')
            		scale = 'F';
          		else
            		print_error("Invalid argument passed in for scale. Only valid options are 'C' and 'F'");
          		break;
        	//Check if log file is passed in
        	case LOG: 
        		if (optarg) {
            		//Try opening the filestream
            		//Append; open or create file for update, writing at end-of-file.
            		log_file = fopen(optarg, "a+");
            		//Returns a null ptr if it fails to open, otherwise returns a pointer to the file stream
            		if (!log_file)
              			print_error("Failed to open log file correctly");
          		}
          		break;
        	//Default case if invalid/incorrect arguments passed in
        	default: 
          		incorrect_arguments();
          		break;
      	}
    }
    
    //Detects running platform and attempts to use included pinmap, this is run on module/library init/load 
    //but is handy to rerun to check board initialised correctly.
    mraa_init();
    
    //Try initializing both the sensors
    initialize_button();
    initialize_sensor();

    cmdsPoll.fd = STDIN_FILENO;
    //The field events is an input parameter, a bit mask specifying the events the application is interested 
    //in for the file descriptor fd.
    //POLLIN: There is data to read
    cmdsPoll.events = POLLIN;

	//Create memory to read in string from STDIN during run time
	char *user_input = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    if (!user_input)
		print_error("Failed to allocate enough memory to store user input");

    //Need to check for stdin based events, as well as continue logging until a button press/OFF is detected
    while(1 == 1) {
		//Generate your first report before you start processing input commands
		/*The sanity check script will send a series of commands to your program, and some implementations process all 
		the commands before generating any reports.*/
		log_entry();
        //Check for commands and if new commands have been issued -> bring changes into effect
        int ret = poll(&cmdsPoll, 1, 0);
        //On error, -1 is returned, and errno is set appropriately.
        if (ret < 0)
          	print_error_with_errno("Failure while polling for commands", errno);
        //A value of 0 indicates that the call timed out and no file descriptors were ready
        //Just go back to the start of the while loop without continuing since no file descriptors were ready
        else if (ret == 0)
          	continue;
		//Otherwise polling was succesful
		else {
			//fgets reads from a FILE* (file stream)
			fgets(user_input, BUFFER_SIZE, stdin);
			//Process the text that was just read in to determine the appropriate action to be taken
			process_inputs(user_input);
		}
    }

	//Free Allocated Memory
	free(user_input);
	user_input = NULL;

    //Close the logfile if it is open, and close all sensors
    close_file_and_sensors();

    //Exit with status 0 if program runs successfully
    return 0;
}