#NAME: Arnav Garg
#UID: 304911796
#EMAIL: arnavgrg@ucla.edu
#SLIPDAYS: 1

#To read/parse through the CSV
import csv
#Helps process command line arguments 
import argparse
# System specific parameter and functions
# sys needed for system calls such as sys.exit, sys.argv and sys.write.stderr
import sys
# To see if file exists in the system (if the file is a valid file_
import os.path

#Modelling code based on Lab3A
#http://web.cs.ucla.edu/classes/cs111/Samples/

#TODO:
#See if assert statements need to be converted to if statements with the correct exit codes

#Class to hold SUPERBLOCK information retrieved from CSV file
class SuperBlock:
    pass

#Class to hold Block group information retrieved from CSV file
class GroupBlock:
    pass

#Class to hold BLOCK information retrieved from CSV file
class Block:
     
    #Constructor for a Block class instance
    #Default: Level of indirection for the block is zero, and reference number if none
    def __init__(self, num, parent_inode, offset, free, level_of_indirection = 0, ref_num = None):
        self.__num = num
        self.__parent_inode = parent_inode
        self.__offset = offset
        self.__free = free
        self.__level_of_indirection = level_of_indirection
        if(ref_num != None):
            self.ref_num = ref_num
        #This must be equal to a value and cannot be unassigned
        assert(self.__num != None)
        #Level of indirection must be 0, 1, 2 or 3
        assert(self.__level_of_indirection > -1 and self.__level_of_indirection < 4)
    
    #Find level of indirection for the block and return the required string
    def indirectionToString(self):
        #If the level of indirection is 0, return an empty string (essentially, nothing)
        if(self.__level_of_indirection == 0):
            return ''
        #If the level of indirection is 1, 2 or 3 we want to return to corresponding 
        #required string
        elif(self.__level_of_indirection == 1):
            return ' INDIRECT'
        elif(self.__level_of_indirection == 2):
            return ' DOUBLE INDIRECT'
        elif(self.__level_of_indirection == 3):
        return ' TRIPLE INDIRECT'
    
    #Check if a block is valid
    def is_valid(self):
        #Need to make sure a value is assigned, and if it is, return the condition below.
        if(Block.total_num_blocks is not None):
            return self.__num > 0 and self.__num < Block.total_num_blocks
        #Otherwise, return an error and exit with status 1
        exit_1("Error! Total number of blocks in super node is NONE\n")
    
    reserved_blocks = [0, 1, 2]

#Helper function to write to stderr and exit with status 2
def exit_2(string):
    '''
    Use this for successful execution, inconsistencies found
    '''
    sys.stderr.write(string)
    sys.exit(2)

#Helper function to write to stderr and exit with status 1
def exit_1(string):
    '''
    Use this for unsuccessful execution, bad parameters or system call failure.
    '''
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

#Helper function for process_superblock
def update_blk(num_blocks, block_size):
    '''
    Updates total_num_blocks and block_size member variables in the Block class
    '''
    Block.total_num_blocks = num_blocks
    Block.block_size = block_size
        
#Helper method to process superblock info from CSV
def process_superblock(reader):
    '''
    This method looks for the row starting with 'superblock' and processes it,
    assigning the corresponding member variables in the respective classes new
    values. It returns this to fill_fields.
    '''
    #Go through the reader iterable
    for row in reader:
        #If we find a row that contains SUPERBLOCK
        if 'SUPERBLOCK' in row:
            #Initialize super_info to be a new instance of the class SuperBlock()
            super_info = SuperBlock()
            #Need to typecast all values in the row from string to integers
            #All of these values get added as member variables of their respective
            #classes if they don't already exist, or are updated to the new values 
            #if they exist
            super_info.total_num_blocks = int(row[1])
            super_info.total_num_inodes = int(row[2])
            super_info.block_size = int(row[3])
            super_info.inode_size = int(row[4])
            super_info.blocks_per_group = int(row[5])
            super_info.inodes_per_group = int(row[6])
            super_info.first_inode = int(row[7])
            #Update Block
            update_blk(int(row[1]), super_info.block_size)
            return super_info

#Create instance of group block and return this object after initializing its values
def process_group_block(reader):
    '''
    This method looks for the row that contains 'GROUP' in it, creates an instance of 
    a GroupBlock object, assigns its member variables some values from this CSV row, 
    and returns the processed instance to fill_fields.
    '''
    #Go through the reader iterable
    for row in reader:
        #If we find a row that contains GROUP
        if 'GROUP' in row:
            #Initialize group_info to be a new instance of the class GroupBlock()
            group_info = GroupBlock()
            group_info.block_bitmap_num = int(row[6])
            group_info.inode_bitmap_num = int(row[7])
            group_info.first_block_of_inodes_num = int(row[8])
            return group_info

#Fill
def fill_fields(file_name):
    '''
    
    - Creates a reader object to iterate over the given CSV file
    - Creates processed instances of Superblocks and Block groups
    '''
    #Opens a file, processes its contents and closes the file
    with open(file_name) as csv_file:
        #Return a reader object which will iterate over lines in the given csvfile.
        csv_reader = csv.reader(csv_file, delimiter=",")
        super_info = process_superblock(csv_reader)
        #Go to the beginning of the file
        csv_file.seek(0)
        #Retrieve info for all the block groups in the file system
        reserved_info = process_group_block(csv_reader)
        #Calculate inode table size
        inode_table_size = (super_info.total_num_inodes * super_info.inode_size)
        #We already have an array corresponding to reserved blocks [0, 1 and 2]
        #Append the retrieved block_bitmap_num and inode_bitmap_num to the reserved 
        #blocks array
        Block.reserved_blocks.append(reserved_info.block_bitmap_num)
        Block.reserved_blocks.append(reserved_info.inode_bitmap_num)
        #Calculate the the number of the last block of inodes
        last_block_of_inodes_num = reserved_info.first_block_of_inodes_num + (inode_table_size / super_info.block_size) + (0, 1)[inode_table_size % super_info.block_size is not 0]
        #Total number of blocks reserved for the inode table lies between first block and last block
        reserved_for_inode_table = range(reserved_info.first_block_of_inodes_num, last_block_of_inodes_num)
        #Add the range of blocks that are reserved to the reserved blocks array
        #This adds an iterable to go through the range of blocks reserved for the inode table
        Block.reserved_blocks += reserved_for_inode_table
        #Reset seek to 0
        csv_file.seek(0)
        #Initialize a new dictionary called block_map to create a key-value mapping
        block_map = {}

#Main function
def main():
    '''
    Main function for the module.
    - Parses CLI arguments to find .csv file
    - Writes to stderr and exits if failure while opening a file
    - Calls helper methods to analyze file system summaries and report inconsistencies
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
