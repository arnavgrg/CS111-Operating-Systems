/* 
NAME: Arnav Garg
UID: 304911796
EMAIL: arnavgrg@ucla.edu
*/

#include <stdio.h>
#include <sys/types.h> //For __uint32_t and __int32_t datatypes
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

//Include given header file that explains data structures used in ext2_fs.h
#include "ext2_fs.h"

//Main function
int main(int argc, const char* argv[]){
    //Make sure argc is 2 so one file (the image) is passed in
    if (argc != 2){
        fprintf(stderr, "Need to pass in exactly one disk image file\n");
        fflush(stderr);
        exit(1);
    }
    //Try opening the disk image file
    int di_fd = open(argv[1], O_RDONLY);
    if (di_fd < 0) {
        fprintf(stderr, "Error opening file system image - %s\n", argv[1]);
        fflush(stderr);
        exit(2);
    }
    //Completed successfully so exit with status 0
    exit(0);
}   