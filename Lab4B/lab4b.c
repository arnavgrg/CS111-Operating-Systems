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
#define STOP   'x'
#define START  'a'
#define LOG    'l'
#define OFF    'o'

//Initialize a global static variable called period to 1
static int period = 1;
static char scale = 'F';
static char* log_file = NULL;

//Create instances of the Sensor & Button
mraa_aio_context sensor;
mraa_gpio_context button;

//Initialize temperature sensor
void initialize_sensor(){
    //Initialise an Analog input device, connected to the specified pin. 
    //Aio pins are always 0 indexed reguardless of their position.
    //Grove Temperature Sensor to the Analog A0/A1 connector on your Grove cape, where it will be addressed as I/O pin #1.
    sensor = mraa_aio_init(0);
    //Check if the sensor failed to initialize
    if (!sensor){
       fprintf(stderr, "Temperature sensor failed to initialize correctly: %d - %s\n", errno, strerror(errno));
       fflush(stderr);
       exit(1);
    }
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
    if (!button){
       fprintf(stderr, "Button failed to initialize correctly: %d - %s\n", errno, strerror(errno));
       fflush(stderr);
       exit(1);
    }
}

//Convert reading into a temperature
//http://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/
float temp_convert(float a){
    int B = 4275;
    int R_0 = 100000;
    float R = R_0 * (1023.0/(a-1.0);
    return 1.0/(log(R/R_0)/B+1/298.15)-273.15;
}

//Temperature is in farhenheit by default
//Function to convert farhenheit to celcius
float f_to_c (float f){
    return (f-32/1.8);
}

//Function to get time in the correct format
void get_time(char *real_time){
    time_t current;
    time(&current);
    struct tm *localTimeNow = localtime(&current);
    if (!localTimeNow) {
        fprintf(stderr, "Failure initializing struct tm\n");
        fflush(stderr);
        exit(1);
    }
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
      {"stop",   no_argument,       NULL, STOP},
      {"start",  no_argument,       NULL, START},
      {"log",    optional_argument, NULL, LOG},
      {"off",    no_argument,       NULL, OFF},
      {0,0,0,0}
    }
  
    //Main getopt while loop to process CLI arguments    
    while ((choice = getopt_long(argc, argv, "", choices, &option_index)) != -1) {
      switch(choice) {
        //Case Period: sampling interval
        case PERIOD: 
          if (atoi(optarg) < 0){
              fprintf(stderr, "Period cannot be a negative value\n");
              fflush(stderr);
          }
          if (optarg)
              period = atoi(optarg);    
          break;
        //Case to process whether the decided scale is F or C
        case SCALE: 
          if (strcmp(optarg,'C') == 0)
            scale = 'C';
          else if (strcmp(optarg, 'F') == 0)
            scale = 'F';
          else {
           fprintf(stderr, "Invalid argument passed in for scale. Only valid options are 'C' and 'F'\n");
           fflush(stderr);
           exit(1);
          } 
          break;
        //Case STOP
        case STOP: break;
        //Case START
        case START: break;
        //Case OFF      
        case OFF: break;
        //CASE LOG
        case LOG: 
          if (optarg)
              log_file = optarg;
          break;
        //Default case if invalid/incorrect arguments passed in
        default: 
          fprintf(stderr, "Invalid argument %s passed in\n", optarg);
          fflush(stderr);
          break;
      }
    }
    
    //Try initializing both the sensors
    initialize_sensor();
    initialize_button();
    
    //Exit with status 0 if program runs successfully
    exit(0);
}