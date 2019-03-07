#NAME: Arnav Garg
#ID: 304911796
#EMAIL: arnavgrg@ucla.edu

#Libraries
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
static char fd = '1';

//Create instances of the Sensor & Button
mraa_aio_context sensor;
mraa_gpio_context button;

void initialize_sensor(){
    //Initialise an Analog input device, connected to the specified pin. 
    //Aio pins are always 0 indexed reguardless of their position.
    sensor = mraa_aio_init(0);
    if (!sensor){
       fprintf(stderr, "Temperature sensor failed to initialize correctly: %d - %s\n", errno, strerror(errno));
       fflush(stderr);
       exit(1);
    }
}

void initialize_button(){
    //Initialise gpio_context, based on board number
    //Pin number read from the board, i.e IO3 is 3
    button = mraa_gpio_init(3);
    if (!button){
       fprintf(stderr, "Button failed to initialize correctly: %d - %s\n", errno, strerror(errno));
       fflush(stderr);
       exit(1);
    }
}

int main(int argc, char* argv[]){
    //Needed for getopt_long
    int choice;
    //Set option_index for getopt_long
    int option_index = 0;
  
    static struct option choices[] = {
      {"period", optional_argument, NULL, PERIOD},
      {"scale",  optional_argument, NULL, SCALE},
      {"stop",   no_argument,       NULL, STOP},
      {"start",  no_argument,       NULL, START},
      {"log",    optional_argument, NULL, LOG},
      {"off",    no_argument,       NULL, OFF},
      {0,0,0,0}
    }
  
    while ((choice = getopt_long(argc, argv, "", choices, &option_index)) != -1) {
      switch(choice) {
        case PERIOD: 
          if (atoi(optarg) < 0){
              fprintf(stderr, "Period cannot be a negative value\n");
              fflush(stderr);
          }
          period = atoi(optarg);    
          break;
        case SCALE: 
          if (optarg != 'C' || optarg != 'F'){
           fprintf(stderr, "Invalid argument passed in for scale. Only valid options are 'C' and 'F'\n");
           fflush(stderr);
           exit(1);
          } 
          scale = optarg[0];
          break;
        case STOP: break;
        case START: break;
        case LOG: 
          if (optarg)
              fd = optarg[0];
          break;
        case OFF: break;
        default: 
          fprintf(stderr, "Invalid argument %s passed in\n", optarg);
          fflush(stderr);
          break;
      }
    }
    
    //Try initializing both the sensors
    initialize_sensor();
    initialize_button();
}
