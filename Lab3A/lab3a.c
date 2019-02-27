/* 
NAME: Arnav Garg
UID: 304911796
EMAIL: arnavgrg@ucla.edu
*/

//Libraries
#include <stdio.h>
#include <sys/types.h> //For __uint32_t and __int32_t datatypes
#include <stdlib.h>
#include <string.h> //For bzero
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h> //For pread 
#include <math.h>
#include <time.h>

//Include given header file that explains data structures used in ext2_fs.h
#include "ext2_fs.h"

//Superblock is located in sector 3 of the disk, with a 1024 byte offset
const unsigned int S_OFFSET = 1024;

//Save size/offset values so we don't need to keep redefining them for the super block
const unsigned int S_INODE_COUNT_SIZE = 4;      // s_inodes_count
const unsigned int S_BLOCK_COUNT_SIZE = 4;      // s_blocks_count
const unsigned int S_LOG_BLOCK_SIZE = 4;   // s_log_block_size
const unsigned int S_INODE_SIZE= 2;       // s_inode_size
const unsigned int S_BLOCKS_PER_GROUP_SIZE = 4; // s_blocks_per_group
const unsigned int S_INODES_PER_GROUP_SIZE = 4; // s_inodes_per_group
const unsigned int S_FIRST_INODE_SIZE = 4;      // s_first_ino
const unsigned int S_ERRORS_SIZE = 2;           // s_errors

//Save size/offset values so we don't need to keep redefining them for group descriptor table
const unsigned int GROUP_DESC_BLOCK_OFFSET = 2048;
const unsigned int GROUP_DESC_TABLE_SIZE = 20;

//Save size/offset values so we don't need to keep redefining them for individual block groups
const unsigned int BG_BLOCK_BITMAP_PTR_SIZE = 4;      // bg_block_bitmap
const unsigned int BG_INODE_BITMAP_PTR_SIZE = 4;      // bg_inode_bitmap
const unsigned int BG_FIRST_INODE_BLOCK_PTR_SIZE = 4; // bg_inode_table
const unsigned int BG_FREE_BLOCKS_COUNT_SIZE = 2;     // bg_free_blocks_count
const unsigned int BG_FREE_INODES_COUNT_SIZE = 2;     // bg_free_inodes_count

//Save buffer size globally
const unsigned int BUFFER_SIZE = 64; 

//Struct to hold all the data in the superblock
typedef struct filesys_superblock_info {
    unsigned int blocks_count; //Total number of blocks (used and free)
    unsigned int inodes_count; //Total number of inodes (used and free)
    unsigned int block_size; //Block size (in bytes) 
    unsigned int inode_size; //Inode size (in bytes)
    unsigned int blocks_per_group; //Total number of blocks per group
    unsigned int inodes_per_group; //Total number of inodes per group
    unsigned int first_inode; //First non-reserved inode
} Info;

//Struct to hold all the data in each group described in the block descriptor table
typedef struct filesys_group_info {
    unsigned short group_num; //Serves as a unique group number
    unsigned long blocks_count; //Total number of blocks in the group
    unsigned int inodes_count; //Total number of inodes in the group
    unsigned int free_inodes_count; //Total number of free indoes in the group
    unsigned int free_blocks_count; //Total number of free blocks in the group
    unsigned int block_bitmap_num; //Block number of free block bitmap for this group
    unsigned int inode_bitmap_num; //Block number of free inode bitmap for this group
    unsigned int first_inode_block_num; //Block number of first block of inodes in this group
} Group;

//Other global variables
//Keep track of file descriptor when disk image file is opened
static int di_fd = -1;
//Global buffer
static void *buf = NULL;
//Global variable to ensure other functions can see info stored in super block
Info super_info;
//The block group descriptor table is an array of block group descriptor, used to define parameters of all the block groups. 
Group *group_descriptor_array = NULL;
//Variable to store total number of groups in the image
static unsigned int num_groups = -1;
//Variable to process bitmap
short* bg_bitmap = NULL;

//Free all memory to prevent memory leaks
void free_memory() {
    free(buf);
    free(group_descriptor_array);
    free(bg_bitmap);
}

//Helper method to write flush stream and exit with status 1
void exit_1() {
    fflush(stderr);
    free_memory();
    exit(1);
}

//Helper method to write flush stream and exit with status 2
void exit_2() {
    fflush(stderr);
    free_memory();
    exit(2);
}

//Function to check # of arguments passed into the CLI
void check_arguments(int args) {
    if (args != 2) {
        fprintf(stderr, "Need to pass in exactly one disk image file\n");
        exit_1();
    }
}

//Read file and check for errors 
int read_file(char* filename) {
    //Open the file in read only mode
    di_fd = open(filename, O_RDONLY);
    //If failure to open the file
    if (di_fd < 0) {
        fprintf(stderr, "Error opening file system image - %s\n", filename);
        exit_2();
    }
    //Create instance of stat struct to determine info about the file
    struct stat st;
    fstat(di_fd, &st);
    //If file size is 0, write to stderr and exit
    if (!st.st_size) {
        fprintf(stderr, "File size is 0. Corrupted disk image file.\n");
        exit_2();
    }
    return di_fd;
}

//Read data into a buffer from the given offset
void read_fs_offset(void *buf, size_t count, off_t offset) {
    //read from or write to a file descriptor at a given offset
    /*pread() reads up to count bytes from file descriptor fd at offset
    offset (from the start of the file) into the buffer starting at buf.
    The file offset is not changed*/
    ssize_t data = pread(di_fd, buf, count, offset);
    //Check if sys call failed
    if (data < 0){
        fprintf(stderr, "Failure reading from file system image: %d - %s", errno, strerror(errno));
        exit_2();
    }
    //Check if number of bytes read in is equal to the number of bytes specified
    else if ((size_t)data != count) {
        fprintf(stderr, "Failure to read in %zu number of bytes from file system image\n", count);
        exit_2();
    }
}

//Function to fill the given field of a struct
void fill_field(void *field, void *buf, size_t field_size, off_t offset) { 
    //Create a local variable to point to the field of the struct passed in
    unsigned int *current_field = field; 
    //Reinitialize the value to 0 incase it had a pre-existing value
    *current_field = 0;
    //Read the required data into the buffer
    read_fs_offset(buf, field_size, offset);
    //Go through the given size of the field and update current_field
    for (size_t i=0; i < field_size; i++) {
        *current_field |= *(((unsigned int *)buf) + i) << (8 * i);
    }
    //Clean buffer by ensuring it has 0 bytes stored in it
    bzero(buf, BUFFER_SIZE);
}

//Write CSV styled output to stdout for superblock
void write_superblock_output() {
    printf("%s,%u,%u,%u,%u,%u,%u,%u\n", 
            "SUPERBLOCK", 
            super_info.blocks_count, 
            super_info.inodes_count, 
            super_info.block_size, 
            super_info.inode_size, 
            super_info.blocks_per_group, 
            super_info.inodes_per_group, 
            super_info.first_inode);
    fflush(stdout);
}

//Reads super block from disk image file and updates the global super_block struct instance
void read_superblock() {
    //Allocate 64 bytes of memory and save it in buf
    buf = malloc(BUFFER_SIZE);
    //If malloc fails, write to stderr and exit
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation for buffer in read_superblock() failed\n");
        exit_2();
    }
    //Ensure the buffer allocated is empty and has no memory in it
    bzero(buf, BUFFER_SIZE);
    //Variable to change offset to the required offset count before updating each field
    off_t offset;
    
    //Update inodes_count field
    //Inodes count starts at offset 0
    offset = 0;
    fill_field(&super_info.inodes_count, buf, S_INODE_COUNT_SIZE, S_OFFSET + offset);
    
    //Update blockes_count field
    //Blocks count starts at offset 4, which is right after S_INODE_COUNT_SIZE
    offset = S_INODE_COUNT_SIZE;
    fill_field(&super_info.blocks_count, buf, S_BLOCK_COUNT_SIZE, S_OFFSET + offset);
    
    //Update block size
    unsigned int block_size;
    //This is the offset where the 4bytes of s_log_block_size are stored
    offset = 24;
    fill_field(&block_size, buf, S_LOG_BLOCK_SIZE, S_OFFSET + offset);
    /*The block size is computed using this 32bit value as the number of bits to shift 
    left the value 1024. This value may only be positive.
        block size = 1024 << s_log_block_size;*/
    //First check to see if there is an error in the block size returned
    if (block_size > 64) {
        fprintf(stderr, "Invalid block size in superblock\n");
        exit_2();
    }
    //Otherwise, update the necessary field in the super_block instance
    super_info.block_size = 1024 << block_size;

    //Create a stat struct to measure the image size
    struct stat st;
    //Calculate size and store it in st.
    fstat(di_fd, &st);
    //Number of blocks * size of each block should be <= image size
    if (super_info.block_size * super_info.blocks_count > st.st_size) {
        fprintf(stderr, "Invalid block count %u or block size values %u\n", 
                            super_info.blocks_count, super_info.block_size);
        exit_2();
    }
    
    //Update inode_size
    //This is the offset where the 2bytes of s_inode_size are stored
    offset = 88;
    fill_field(&super_info.inode_size, buf, S_INODE_SIZE, S_OFFSET + offset);
    //In revision 0, this value must always be 128
    //In revision one, this must be a perfect power of 2 and must be smaller or equal to the block size (1<<s_log_block_size).    
    //Check if it is not a perfect power of 2 since 128 is also a perfect power of 2
    if ( !((super_info.inode_size & (super_info.inode_size - 1)) == 0) ) {
            fprintf(stderr, "Invalid inode size %u, not a power of 2\n", super_info.inode_size);
            exit_2();
    }

    //Update blocks per group
    //This is the offset where the 4bytes of s_blocks_per_group are stored
    offset = 32;
    fill_field(&super_info.blocks_per_group, buf, S_BLOCKS_PER_GROUP_SIZE, S_OFFSET + offset);
    //Block count should be lower or equal to (s_blocks_per_group * number of block groups)
    //Therefore, total number of blocks must be a multiple of number of blocks in every group
    /*if (super_info.blocks_count % super_info.blocks_per_group) {
        fprintf(stderr, "Invalid blocks per group %u or blocks count %u\n", super_info.blocks_per_group, 
                super_info.blocks_count);
        exit_2();
    }*/

    //Update Inodes per group
    //This is the offset where the 4bytes of s_inodes_per_group are stored
    offset = 40;
    fill_field(&super_info.inodes_per_group, buf, S_INODES_PER_GROUP_SIZE, S_OFFSET + offset);

    //Update first non-reserved inode value
    //This is the offset where there 4bytes of s_first_ino are stored
    offset = 84;
    fill_field(&super_info.first_inode, buf, S_FIRST_INODE_SIZE, S_OFFSET + offset);

    //Call helper method to write data to stdout
    write_superblock_output();
}

//Helper method to initialize a block descriptor array with enough memory
void initialize_group_descriptor_array() {
    //Allocate enough memory to hold num_groups Groups in array
    group_descriptor_array = malloc(sizeof(Group) * num_groups);
    //Check if malloc failed
    if (!group_descriptor_array){
        fprintf(stderr, "Failed to allocate memory for block group descriptor array\n");
        exit_2();
    }
}

//Helper function for read_group_block_descriptors to determine block count for a given group
void update_group_block_count(Group *g) {
    //Create local variables to store values from the superblock
    unsigned int total_blocks = super_info.blocks_count;
    unsigned int blocks_per_group = super_info.blocks_per_group;
    /*all cylinder groups but the last have the same number of blocks and I-nodes; the last 
    has the residue (e.g., blocks/fs modulo blocks/group).*/
    //Check if the total number of blocks is greater than the number of blocks in a group
    //If this is true
    if (total_blocks > blocks_per_group) {
        //If the group number for the current block is equal to the last group
        if (g->group_num == num_groups - 1) {
            //Set blocks_count for this group to the remainder of below expression
            g->blocks_count = total_blocks % blocks_per_group;
        } 
        //Otherwise, we simply set blocks_count for this group to the number of blocks in 
        //every group
        else {
            g->blocks_count = blocks_per_group;
        }
    } 
    //If the above condition was never true, then just set the blocks_count
    //for this group to the total number of blocks in the superblock
    else {
        g->blocks_count = total_blocks;
    }
}

//Helper method to write CSV styled output for each group to stdout
void write_group_output(Group *g_block_info) {
    printf("%s,%u,%lu,%u,%u,%u,%u,%u,%u\n",
            "GROUP", 
            g_block_info->group_num, 
            g_block_info->blocks_count, 
            g_block_info->inodes_count, 
            g_block_info->free_blocks_count, 
            g_block_info->free_inodes_count, 
            g_block_info->block_bitmap_num, 
            g_block_info->inode_bitmap_num, 
            g_block_info->first_inode_block_num);
    fflush(stdout);
}

//Function to read through Block Group Descriptor Table and find values for each group
Group read_group_block_descriptors(unsigned int group_number, const unsigned int offset) {
    //Initialize an instance of a Group
    Group g_block_info;
    //Assign group number member to the value passed into the function
    g_block_info.group_num = group_number;
    //Reset before to be empty
    bzero(buf, BUFFER_SIZE);
    //Call helper function to update group block count number
    update_group_block_count(&g_block_info);
    
    //Update inodes_count for current block
    fill_field(&g_block_info.inodes_count, buf, S_INODE_COUNT_SIZE, S_OFFSET);
    
    //Update block_bitmap for current block
    off_t bg_offset = 0;
    fill_field(&g_block_info.block_bitmap_num, buf, BG_BLOCK_BITMAP_PTR_SIZE, offset + bg_offset);
    
    //Update inode_bitmap for current block
    //This is the offset for bg_inode_bitmap of size 4bytes in the block group descriptor table of the image
    bg_offset += BG_BLOCK_BITMAP_PTR_SIZE;
    fill_field(&g_block_info.inode_bitmap_num, buf, BG_INODE_BITMAP_PTR_SIZE, offset + bg_offset);

    //Update first_inode_block_num for current block
    //This is the offset for bg_inode_bitmap of size 4bytes in the block group descriptor table of the image
    bg_offset += BG_INODE_BITMAP_PTR_SIZE;
    fill_field(&g_block_info.first_inode_block_num, buf, BG_FIRST_INODE_BLOCK_PTR_SIZE, offset + bg_offset);

    //Update free_blocks_count for current block
    //This is the offset for bg_free_blocks_count of size 2bytes in the block group descriptor table of the image
    bg_offset += BG_FIRST_INODE_BLOCK_PTR_SIZE;
    fill_field(&g_block_info.free_blocks_count, buf, BG_FREE_BLOCKS_COUNT_SIZE, offset + bg_offset);

    //Update free_inodes_count for current block
    //This is the offset for bg_free_inodes_count of size 2bytes in the block group descriptor table of the image
    bg_offset += BG_FREE_BLOCKS_COUNT_SIZE;
    fill_field(&g_block_info.free_inodes_count, buf, BG_FREE_INODES_COUNT_SIZE, offset + bg_offset);

    //Call helper function to write data to stdout
    write_group_output(&g_block_info);

    //Return the block after filling its required fields.
    return g_block_info;
}

//Helper function to process the bitmap for process_free_block
short* process_bitmap(unsigned long bits_long, off_t offset) {
    //Malloc enough memory to store all the bits in the bitmap
    short* temp = malloc(sizeof(short) * bits_long);
    //If malloc fails, write to stderr and exit
    if (!temp) {
        fprintf(stderr, "Malloc failed while processing bitmap\n");
        exit_2();
    }
    //Create character buffer
    signed char* buffer = malloc(BUFFER_SIZE);
    //If malloc fails, write to stderr and exit
    if (!buffer) {
        fprintf(stderr, "Error creating character buffer while processing bitmap\n");
        exit_2();
    }
    //Need to determine the right offset value/where in the byte we are while 
    //determing the value of the bit in that byte
    size_t count = 0;
    if (bits_long % 8 == 0)
        count = 0;
    else
        count = 1;
    //Read the data from the correct offset in the image
    read_fs_offset(buffer, (bits_long / 8) + count, offset);
    //Process all the bits in the bitmap one by one
    /*The first block of this block group is represented by bit 0 of byte 0, the 
    second by bit 1 of byte 0. The 8th block is represented by bit 7 (most significant bit) 
    of byte 0 while the 9th block is represented by bit 0 (least significant bit) of byte 1.*/
    for(unsigned long bit_index=0; bit_index < bits_long; bit_index++) 
        temp[bit_index] = (buffer[bit_index/8] >> (bit_index % 8)) & 1;
    //Free allocated memory for character buffer since we no longer need it
    free(buffer);
    //Return malloc'd object to bg_bitmap in process_freeblock
    return temp;
}

//Function to process free blocks in each of the groups
void process_freeblocks(unsigned long num_blocks, unsigned long block_bitmap_offset) {
    /*Each bit represent the current state of a block within that block group, 
    where 1 means "used" and 0 "free/available".*/
    bg_bitmap = process_bitmap(num_blocks, block_bitmap_offset);
    //Go through each of the bits in the bitmap
    for (unsigned long i=0; i < num_blocks; i++) {
        //If the bit is 0 (free), then we want to write the CSV styled line
        if (bg_bitmap[i] == 0) {
            printf("BFREE,%u\n",(unsigned int)i+1);
            fflush(stdout);
        }
    }
}

//Main function
int main(int argc, char* argv[]) {
    //Make sure argc is 2 so one file (the image) is passed in
    check_arguments(argc);
    //Try opening the disk image file and check if file size is > 0
    read_file(argv[1]);
    /*Always want to load the superblock first The layout on disk is very predictable 
    as long as you know a few basic information; block size, blocks per group, inodes 
    per group. This information is all located in, or can be computed from, the super
    block structure.*/
    //Read superblock
    read_superblock();
    //Calculate total number of groups from info in superblock
    num_groups = (super_info.blocks_count / super_info.blocks_per_group) + 1;
    //Initialize group descriptor array
    initialize_group_descriptor_array();
    //Go through all of the groups and get the necessary values
    for (unsigned int i=0; i < num_groups; i++) {
        //First value always starts at 0 and grows incrementally with each call to the read_group_block_descriptors function
        //It serves as a unique value for each group in the block group descriptor table
        //Second value is the offset in the block group descriptor table to traverse through each of the groups (size 20)
        group_descriptor_array[i] = read_group_block_descriptors(i, (GROUP_DESC_BLOCK_OFFSET + (i * GROUP_DESC_TABLE_SIZE)));
    }
    //Initialize local variables for this for loop
    unsigned long num_blocks_in_group;
    unsigned long block_bitmap_offset;
    //Go through each of the block groups 
    for (unsigned int i=0; i < num_groups; i++) {
        num_blocks_in_group = group_descriptor_array[i].blocks_count;
        block_bitmap_offset = group_descriptor_array[i].block_bitmap_num * super_info.block_size;
        process_freeblocks(num_blocks_in_group, block_bitmap_offset);
    }
    //Free memory before exiting
    free_memory();
    //Completed successfully so exit with status 0
    exit(0);
}