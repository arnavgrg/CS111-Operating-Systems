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
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in structure
#include <netdb.h> // hostent structure
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/evp.h>

#define PERIOD 'p'
#define SCALE  's'
#define LOG    'l'
#define ID     'i'
#define HOST   'h'

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
//Variable to keep track of ID number
char* id_num = "";
//Variable to keep track of host name
char* host_name = "";
//Keep track of the given port number
static int port_num = -1;

//Create instances of the Sensor & Button
mraa_aio_context sensor;

//hostent structure
/*
char  *h_name        Official name of the host.
char **h_aliases     A pointer to an array of pointers to alternative host names,
                     terminated by a null pointer.
int    h_addrtype    Address type.
int    h_length      The length, in bytes, of the address.
char **h_addr_list   A pointer to an array of pointers to network addresses (in
                     network byte order) for the host, terminated by a null pointer.
*/

//sockaddr_in structure
//The sockaddr_in structure is used to store addresses for the Internet protocol family. 
//Values of this type must be cast to struct sockaddr for use with the socket interfaces defined in this document.
/*
sa_family_t      sin_family
in_port_t        sin_port
struct in_addr   sin_addr
unsigned char    sin_zero[8]
*/

//Server
struct hostent *server;
//Socket
struct sockaddr_in server_address;
int sock;

//SSL structures
//Create a new context
SSL_CTX* new_context = NULL;
SSL* ssl = NULL;

//Free memory
void free_memory() {
	free(log_file);
	log_file = NULL;
}

//Print errors and exit
void print_error(char* err) {
    fprintf(stderr, "%s\n", err);
    fflush(stderr);
	free_memory();
    exit(1);
}

//Print errors with errno
void print_error_with_errno(char* err, int error_num) {
    fprintf(stderr, "%s: %d - %s\n", err, error_num, strerror(error_num));
    fflush(stderr);
	free_memory();
    exit(1);
}

//Incorrect arguments/bogus arguments passed into CLI during initial call
void incorrect_arguments() {
	fprintf(stderr, "Invalid argument passed in\n");
    fflush(stderr);
    exit(1);
}

//Helper method to write output to a log file if it is processed
void write_to_log_file(char* str) {
	if (log_file) {
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
char* getTime() {
    time_t current;
    //This function returns the time since 00:00:00 UTC, January 1, 1970 (Unix timestamp) in seconds.
    time(&current);
    //The time returned from localtime(3) will only be in the correct timezone if you have correctly configured 
    //the local timezone on your embedded system.
    struct tm *localTimeNow = localtime(&current);
    if (!localTimeNow)
        print_error("Failure initializing struct tm");
	//Malloc enough space to hold the date
	char* p_time = malloc(sizeof(char) * 10);
	/*The strftime() function formats the broken-down time tm according to the format specification format and places 
    the result in the character array s of size max.*/
    //size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);
    strftime(p_time, 9, "%H:%M:%S", localTimeNow);
	//Return the date string
	return p_time;
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

//Helper function to check if required arguments (host, id, log file) are passed in
void check_for_required_arguments() {
	if (host_name == NULL || strlen(host_name) == 0)
		print_error("Host not specified but is required");
	if (id_num == NULL || strlen(id_num) != 9)
		print_error("ID number was not passed in or has invalid length");
	if (!log_file)
		print_error("Invalid logfile or log file not passed in");
}

//Create socket to help establish a connection with the server
void create_socket() {
	//socket - create an endpoint for communication
	//int socket(int domain, int type, int protocol);
	//Takes 3 parameters:
	//domain: Specifies the communications domain in which a socket is to be created. 
	//type: Specifies the type of socket to be created.
	//protocol: Specifies a particular protocol to be used with the socket. Specifying a protocol of 0 causes 
	//          socket() to use an unspecified default protocol appropriate for the requested socket type.
	//AF_INET -> IPv4
	//SOCK_STREAM -> Provides sequenced, reliable, bidirectional, connection-mode byte streams, and may provide a transmission 
	//				 mechanism for out-of-band data.
	//RETURNS: A socket file descriptor, or -1 for failure
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		print_error_with_errno("Failed to create socket successfully", errno);
}

//Return a hostent structure that gives us more details about the host/server
void get_host() {
	//The gethostbyname() function returns a structure of type hostent for the given host name.
	server = gethostbyname(host_name);
	if (!server)
		print_error_with_errno("Failed to find host", h_errno);
}

//Update sockaddr_in server_address correctly so that we can connect to the server
void update_server_address() {
	//Fill server_address with 0s. 
	//Especially import for the sin.zero[8] field since it is usually set to all 0s
	memset((void *)&server_address, 0, sizeof(server_address));
	//Set family to IPv4 and convert port_num to server/network readable byte order
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port_num);
	//Update address to the address received from gethostbyname
	memcpy((char*)&server_address.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
}

//Establish a connection with the server and send ID number 
void connect_to_server() {
	//This typecast is allowed as specified in the documentation: struct sockaddr * == struct sockaddr_in
	int connect_val = connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));
	//If connect fails, write to stderr and exit
	if (connect_val == -1)
      	print_error_with_errno("Client failed to connect to server", errno);
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
		//Get time from getTemperature function
		float temperature = getTemperature();
		//Initialize a string and get the current time
    	char* p_time = getTime();
		//Write to server
		char time_string[50];
		sprintf(time_string, "%s %.1f\n", p_time, temperature);
		if (SSL_write(ssl, time_string, strlen(time_string)) <= 0)
			print_error("Failed to log time stamp and temperature");
		//If logging is turned on, write to logfile
		if (log_file) {
			fprintf(log_file, "%s %.1f\n", p_time, temperature);
			fflush(log_file);
		}
		//Since we malloc'd, we want to free this memory and assign it back to a null ptr
		free(p_time);
		p_time = NULL;
		//Update next_time to current time + the next period so we only log a 
		//new entry when we hit the next time interval
		next_time = tclock.tv_sec + period;
	}
}

//Logs one final temperature reading and exits
void shut_down() {
	//Otherwise, write to stdout
  	char* p_time = getTime();
	//Write to server
	char out[50];
	sprintf(out, "%s SHUTDOWN", p_time);
  	if (SSL_write(ssl, out, strlen(out)) <= 0)
		print_error("Failed to shutdown");
  	//If there is a log file, write to the logfile
  	if (log_file) {
    	fprintf(log_file, "%s SHUTDOWN", p_time);
		fflush(log_file);
		//Want to free this memory to prevent memory
		free(p_time);
		//Reassign to prevent dangling pointers 
		p_time = NULL;
		//Shutdown and free client
		SSL_shutdown(ssl);
		SSL_free(ssl);
		//Exit with 0 to indicate success
    	exit(0);
  	}
	//If no log file, repeat the same steps described above
	free(p_time);
	p_time = NULL;
	//Shutdown and free client
	SSL_shutdown(ssl);
	SSL_free(ssl);
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
		shut_down();
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
	//Spec says: If logging is enabled, all received commands (valid or not) should be appended to the log file
	else 
		write_to_log_file(input);
	//Reset to null to prevent dangling pointers problems
	period_ptr = NULL;
	log_ptr = NULL;
}

//When change in fd detected, it calls process_inputs and then calls read_from_server
void read_from_server(char* input) {
	//Server returns values such as START PERIOD=7, SCALE=C, STOP, D=3, D= etc.
	//Value saved in input
	int rd = SSL_read(ssl, input, 512);
	if (rd < 0)
		print_error_with_errno("Failed to read from server", errno);
	else 
		//Mark nullbyte at the end of the string so we know where to read till
		input[rd] = '\0';
	process_inputs(input);
}
                     
//Main function
int main(int argc, char* argv[]) {
    //Needed for getopt_long
    int choice;
    //Set option_index for getopt_long
    int option_index = 0;
    
	//Poll struct
    /* If none of the events requested (and no error) has occurred for any of the file descriptors, then 
    poll() blocks until one of the events occurs.*/
    struct pollfd cmdsPoll;

    //Struct containing choices for getopt
    static struct option choices[] = {
		{"period", optional_argument, NULL, PERIOD},
      	{"scale",  optional_argument, NULL, SCALE},
      	{"log",    required_argument, NULL, LOG},
		{"id",     required_argument, NULL, ID},
		{"host",   required_argument, NULL, HOST},
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
			//If ID number is passed in
			case ID:
				if (optarg)
					id_num = optarg;
				break;
			//If a hostname is passed in
			case HOST:
				if (optarg)
					host_name = optarg;
				break;
        	//Default case if invalid/incorrect arguments passed in
        	default: 
          		incorrect_arguments();
          		break;
      	}
    }

	//Process port number
	if (optind < argc)
		port_num = atoi(argv[optind]);
	//If the above condition isn't true, then port number is still -1 so write to stderr and exit
	if (port_num <= 0)
			print_error("Invalid port number");

	//Checks if mandatory arguments were passed in
	check_for_required_arguments();
    //Detects running platform and attempts to use included pinmap
    mraa_init();
	//Try initializing the temperature sensor
    initialize_sensor();
	//Create socket and gethostbyname
	/*To establish an outbound TCP connection it is necessary to specify the remote IP address and port number to 
	which the connection should be directed. The combination of these two values is treated as a single entity called 
	the socket address, which is represented by a struct sockaddr_in for IPv4 or a struct sockaddr_in6 for IPv6.*/
	create_socket();
	//Get host by name
	get_host();
	//Update server_address sockaddr_in struct with the required values to establish a connection with the server
	update_server_address();
	//Create connection with the server and immediately send 9-digit ID number
	connect_to_server();

	//Initialize Library
	if (SSL_library_init() < 0)
		print_error("Failed to initialize openSSL library");

    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

	//Create a new context
	new_context = SSL_CTX_new(TLSv1_client_method());
	if (!new_context)
		print_error("Unable to retrieve SSL context");

	//Create an SSL client
	ssl = SSL_new(new_context);
	if (!ssl)
		print_error("Failed to create SSL client");

	//Associate file descriptor with SSL
	//Returns either 0 (failure) or 1 (success)
	if (!SSL_set_fd(ssl, sock))
		print_error("Failed to associate file descriptor with SSL client");
	
	//Initiate the TLS/SSL handshake with an TLS/SSL server
	if (SSL_connect(ssl) != 1)
		print_error("SSL connection failed");

	//write ID to server
	char out[15];
	sprintf(out, "ID=%s\n", id_num);
	if (SSL_write(ssl, out, strlen(out)) <= 0)
		print_error("Failed to write ID to server");

	//Also write to logfile
	if (log_file) {
		fprintf(log_file, "ID=%s\n", id_num);
		fflush(log_file);
	}

	//POLLIN: There is data to read
    cmdsPoll.fd = sock;
    cmdsPoll.events = POLLIN;

	//Create memory to read in string from STDIN during run time
	char user_input[512];

    //Need to check for stdin based events, as well as continue logging until a button press/OFF is detected
    while(1 == 1) {
		//Generate your first report before you start processing input commands
		/*The sanity check script will send a series of commands to your program, and some implementations process all 
		the commands before generating any reports.*/
		log_entry();
        //Check for commands and if new commands have been issued -> bring changes into effect
        poll(&cmdsPoll, 1, 0);
        if (cmdsPoll.revents & POLLIN)
    		read_from_server(user_input);
    }

    //Close the logfile if it is open, and close all sensors
    close_file_and_sensors();

    //Exit with status 0 if program runs successfully
    exit(0);
}