#NAME: Arnav Garg
#ID: 304911796
#EMAIL: arnavgrg@ucla.edu

#Libraries
#include <stdio.h>
#include <getopt.h>

#define PERIOD 'p'
#define SCALE  's'

#Initialize a global static variable called period to 1
static int period = 1
static char scale = 'F'

int main(int argc, char* argv[]){
    //Needed for getopt_long
    int choice;
    //Set option_index for getopt_long
    int option_index = 0;
  
    static struct option choices[] = {
      {"period", optional_argument, NULL, PERIOD},
      {"scale",  optional_argument, NULL, SCALE},
      {0,0,0,0}
    }
  
    while ((choice = getopt_long(argc, argv, "", choices, &option_index)) != -1) {
      switch(choice) {
        case PERIOD: 
          if (optarg)
              period = atoi(optarg);
          break;
        case SCALE: 
          if (optarg != 'C' || optarg != 'F'){
           fprintf(stderr, "Invalid argument passed in for scale. Only valid options are 'C' and 'F'\n");
           fflush(stderr);
           exit(1);
          } 
          scale = optarg
          break;
        default: break;
      }
    }
}
