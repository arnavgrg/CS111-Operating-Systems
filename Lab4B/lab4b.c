//NAME: Arnav Garg
//ID: 304911796
//EMAIL: arnavgrg@ucla.edu

//Libraries
#include <stdio.h>
#include <getopt.h>
#include <poll.h>
#include <mraa.h>
#include <aio.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>

#define PERIOD 'p'
#define SCALE  's'
#define LOG    'l'

//Initialize a global static variable called period to 1
static int period = 1;
static char scale = 'F';
FILE* log_file = NULL;

//Create instances of the Sensor & Button
mraa_aio_context sensor;
mraa_gpio_context button;

//Print errors and exit
void print_error(char* err){
  fprintf(stderr, "%s\n", err);
  fflush(stderr);
  exit(1);
}

//Print errors with errno
void print_error_with_errno(char* err, int error_num){
    fprintf(stderr, "%s: %d - %s\n", err, error_num, strerror(error_num));
    fflush(stderr);
    exit(1);
}

//Initialize temperature sensor
void initialize_sensor(){
    //Initialise an Analog input device, connected to the specified pin. 
    //Aio pins are always 0 indexed reguardless of their position.
    //Grove Temperature Sensor to the Analog A0/A1 connector on your Grove cape, where it will be addressed as I/O pin #1.
    sensor = mraa_aio_init(0);
    //Check if the sensor failed to initialize
    if (!sensor)
       print_error_with_errno("Temperature sensor failed to initialize correctly", errno);
}

//Initialize button
void initialize_button(){
    //Initialise gpio_context, based on board number
    //GPIO     MRAA
    //GPIO_51   62
    //GPIO_50   60
    //Grove Button attached to the GPIO_50 connector on Grove cape, where it will be addressed as I/O pin #60.
    button = mraa_gpio_init(60);
    //Check if the button failed to initialize
    if (!button)
       print_error_with_errno(stderr, "Button failed to initialize correctly", errno);
    //Set button to be input
    mraa_gpio_dir(button, MRAA_GPIO_IN);
}

//Convert reading into a temperature
//http://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/
float getTemperature(float a){
    int B = 4275;
    int R_0 = 100000;
    float R = R_0 * (1023.0/(a-1.0);
    float result = 1.0/(log(R/R_0)/B+1/298.15)-273.15;
    if (strcmp(scale,'F') == 0)
       return result*1.8 + 32;
    return result;
}

//Function to get time in the correct format
//For this function to work correctly, we need to configure the local timezone on our BeagleBone.
void get_time(char *real_time){
    time_t current;
    time(&current);
    struct tm *localTimeNow = localtime(&current);
    if (!localTimeNow)
        print_error("Failure initializing struct tm");
    strftime(real_time, 9, "%H:%M:%S", localTimeNow);
    //free(localTimeNow);
}
                     
//Main function
int main(int argc, char* argv[]){
    //Needed for getopt_long
    int choice;
    
    //Set option_index for getopt_long
    int option_index = 0;
    
    //Struct containing choices for getopt
    static struct option choices[] = {
      {"period", optional_argument, NULL, PERIOD},
      {"scale",  optional_argument, NULL, SCALE},
      {"log",    required_argument, NULL, LOG},
      {0,0,0,0}
    }
    
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
          else if (strcmp(optarg,'C') == 0)
            scale = 'C';
          else if (strcmp(optarg,'F') == 0)
            scale = 'F';
          else
            print_error("Invalid argument passed in for scale. Only valid options are 'C' and 'F'");
          break;
        case LOG: 
          if (optarg)
              //Try opening the filestream
              log_file = fopen(optarg, "a+");
              if (!log_file)
                print_error("Failed to open log file correctly");
          break;
        //Default case if invalid/incorrect arguments passed in
        default: 
          fprintf(stderr, "Invalid argument %s passed in\n", optarg);
          fflush(stderr);
          exit(1);
          break;
      }
    }
    
    //Detects running platform and attempts to use included pinmap, this is run on module/library init/load 
    //but is handy to rerun to check board initialised correctly.
    mraa_init();
    
    //Try initializing both the sensors
    initialize_sensor();
    initialize_button();
    
    //Exit with status 0 if program runs successfully
    exit(0);
}