#NAME: Arnav Garg
#UID: 304911796
#EMAIL: arnavgrg@ucla.edu

import csv
#Helps process command line arguments 
import argparse
# System specific parameter and functions
# sys needed for system calls such as sys.exit, sys.argv and sys.write.stderr
import sys
import os.path

#http://web.cs.ucla.edu/classes/cs111/Samples/

#Modelling code based on Lab3A

#Class to hold SUPERBLOCK information retrieved from CSV file
class SuperBlock:
    pass

class Block:
    pass

class GroupBlock:
    pass

#Helper function to write to stderr and exit with status 2
#Use this for successful execution, inconsistencies found
def exit_2(string):
    sys.stderr.write(string)
    sys.exit(2)

#Helper function to write to stderr and exit with status 1
#Use this for unsuccessful execution, bad parameters or system call failure.
def exit_1(string):
    sys.stderr.write(string)
    sys.exit(1)

#Helper method to check if arguments passed in are correct
def process_arguments():
    '''
    Helper method to process arguments.
    - Checks if the number arguments passed in are 2
    - Returns an array containing the parsed CLI input to the main function
    '''
    #If number of arguments is not exactly 2, we want to write to stderr and exit
    if len(sys.argv) != 2:
        exit_1("Invalid number of arguments passed in\n")
    #Otherwise, initialize an instance of an Argument Parser
    parser = argparse.ArgumentParser(prog='lab3b', description="Reads a CSV file corresponding to \
                                                     an EXT2 File System Analysis")
    parser.add_argument('filename', nargs=1, help="CSV Filename")
    #Return processed parsed arguments as a vector
    try:
        return parser.parse_args()
    #If it fails, then write to stderr and exit
    except:
        exit_1("Bad arguments detected. Try lab3b --help for more information\n")

#Helper method to process superblock info from CSV
def process_superblock(reader):
    '''
    This method looks for the row starting with 'superblock' and processes it,
    assigning the corresponding member variables in the respective classes new
    values
    '''
    #Go through the reader iterable
    for row in reader:
        #If we find a row that starts with SUPERBLOCK
        if 'SUPERBLOCK' in row:
            #Initialize super_info to be a new instance of the class SuperBlock()
            super_info = SuperBlock()
            #Need to typecast all values in the row from string to integers
            #All of these values get added as member variables of their respective
            #classes if they don't already exist, or are updated to the new values 
            #if they exist
            super_info.total_num_blocks = int(row[1])
            Block.total_num_blocks = int(row[1])
            super_info.total_num_inodes = int(row[2])
            super_info.block_size = int(row[3])
            Block.block_size = super_info.block_size
            super_info.inode_size = int(row[4])
            super_info.blocks_per_group = int(row[5])
            super_info.inodes_per_group = int(row[6])
            super_info.first_inode = int(row[7])
            return super_info

#Create instance of group block and return this object after initializing its values
def process_group_block(reader):
    for row in reader:
        if 'GROUP' in row:
            group_info = GroupBlock()
            group_info.block_bitmap_num = int(row[6])
            group_info.inode_bitmap_num = int(row[7])
            group_info.first_block_of_inodes_num = int(row[8])
            return group_info

#Fill
def fill_fields(file_name):
    '''

    - Creates a reader object to iterate over the given CSV file
    '''
    #Initialize a new dictionary called block_map to create a key-value mapping
    block_map = {}
    #Opens a file, processes its contents and closes the file
    with open(file_name) as csv_file:
        #Return a reader object which will iterate over lines in the given csvfile.
        csv_reader = csv.reader(csv_file, delimiter=",")
        super_info = process_superblock(csv_reader)
        #Go to the beginning of the file
        csv_file.seek(0)
        reserved_info = process_group_block(csv_reader)

#Main function
def main():
    '''
    main function for the module.
    - parses cli arguments to find .csv file
    - writes to stderr and exits if failure while opening a file
    - calls helper methods to analyze file system summaries and report inconsistencies
    '''
    args = process_arguments()
    file_name = args.filename[0]
    #Check if file exists on the system/valid file
    if not os.path.exists(file_name):
        exit_1("Invalid filename or file not found on system\n")
    #If successful with no inconsistencies, exit with 0
    sys.exit(0)

'''
Before execution, python sets up a few special variables and __name__ 
is one of the variables
When it runs a python file, python sets __name__ to __main__
However, we only have one module so this is not necessary
'''
if __name__ == "__main__":
    main()