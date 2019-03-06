#!/usr/bin/python

#NAME: Arnav Garg
#ID: 304911796
#EMAIL: arnavgrg@ucla.edu

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

#Globals
#Keeps track of link counts for different inode entries
inode_links = {}
#Saves a copy of the inode map for directory audits
inode_map_directory_copy = {}
#Keeps track of the inode numbers for free inodes
free_inode_list = []
#If a discrepancy is detected, then we can return with exit status 2
check_for_discrepenacies = 0

#Class to hold SUPERBLOCK information retrieved from CSV file
class SuperBlock:
    def __init__(self, row):
        #Need to typecast all values in the row from string to integers
        #All of these values get added as member variables of their respective
        #classes if they don't already exist, or are updated to the new values 
        #if they exist
        self.total_num_blocks = int(row[1])
        self.total_num_inodes = int(row[2])
        self.block_size = int(row[3])
        self.inode_size = int(row[4])
        self.blocks_per_group = int(row[5])
        self.inodes_per_group = int(row[6])
        self.first_inode = int(row[7])

#Class to hold Block group information retrieved from CSV file
class GroupBlock:
    #Constructor
    def __init__(self, row):
        self.block_bitmap_num = int(row[6])
        self.inode_bitmap_num = int(row[7])
        self.first_block_of_inodes_num = int(row[8])  

#Class to hold BLOCK information retrieved from CSV file
class Block:
    reserved_blocks = [0, 1, 2]
    #Constructor for a Block class instance
    #Default: Level of indirection for the block is zero, and reference number if none
    def __init__(self, num, parent_inode, offset, free, level_of_indirection = 0, ref_num = None):
        self.__num = num
        self.__parent_inode = parent_inode
        self.__offset = offset
        self.__free = free
        self.__level_of_indirection = level_of_indirection
        if ref_num != None:
            self.ref_num = ref_num
        #This must be equal to a value and cannot be unassigned
        assert(self.__num != None)
        #Level of indirection must be 0, 1, 2 or 3
        assert(self.__level_of_indirection > -1 and self.__level_of_indirection < 4)
    
    #Find level of indirection for the block and return the required string
    def indirectionToString(self):
        #If the level of indirection is 0, return an empty string (essentially, nothing)
        if self.__level_of_indirection == 0:
            return ''
        #If the level of indirection is 1, 2 or 3 we want to return to corresponding 
        #required string
        elif self.__level_of_indirection == 1:
            return " INDIRECT"
        elif self.__level_of_indirection == 2:
            return " DOUBLE INDIRECT"
        elif self.__level_of_indirection == 3:
            return " TRIPLE INDIRECT"
    
    #Check if a block is valid
    def is_valid(self):
        #Need to make sure a value is assigned, and if it is, return the condition below.
        if(Block.total_num_blocks is not None):
            return self.__num < Block.total_num_blocks and self.__num > 0 
        #Otherwise, return an error and exit with status 1
        exit_1("Error! Total number of blocks in super node is NONE\n")

    #Need to create functions to return values of member variables
    #This helps simplify processing block consistency audits

    #Method to return the block's number
    def getNum(self):
        return self.__num

    #Method to see if block is Free or not
    def freeStatus(self):
        return self.__free

    #Method to return inode number
    def getInode(self):
        return self.__parent_inode
    
    #Method to return offset
    def getOffset(self):
        return self.__offset

    #Check if a block is reserved
    def isReserved(self):
        if self.__num in Block.reserved_blocks:
            return True
        return False

#Class to hold directory information
class Directory:
	def __init__(self, row):
		self.parent_inode_num = int(row[1])
		self.self_inode_num = int(row[3])
        #rstrip helps remove any unused/trailing characters from the name
		self.file_name = row[6].rstrip()

#Helper function to write to stderr and exit with status 2
def exit_2(string):
    ''' Use this for successful execution, inconsistencies found '''
    sys.stderr.write(string)
    sys.exit(2)

#Helper function to write to stderr and exit with status 1
def exit_1(string):
    ''' Use this for unsuccessful execution, bad parameters or system call failure. '''
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
def update_block(num_blocks, block_size):
    ''' Updates total_num_blocks and block_size member variables in the Block class '''
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
            super_info = SuperBlock(row)
            #Update Block
            update_block(int(row[1]), super_info.block_size)
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
            group_info = GroupBlock(row)
            return group_info

#Insert the initialized block into the block hash map
def insert_block_into_map(b, block_hash_map):
    ''' This function inserts the processed Block into our hashmap. '''
    #Hashmap maps block's num to the block
    #If this block's number is not already in the hashmap, then we place the block
    #in an array and set the key to the block's key number.
    if b.getNum() not in block_hash_map:
        block_hash_map[b.getNum()] = [b]
    #If it already exists in the hashmap, we just append it to our array of blocks
    #This is necessary since many blocks may/will have the same block number 
    else:
        block_hash_map[b.getNum()].append(b)

def find_logical_offset(num_ptrs_in_current_block, index_in_inode_table):
    '''
    This finds the required offset, or essentially the required offset to process
    every block the pointers are pointing to.
    '''
    #If this condition is true, then we're in the first 12 blocks, so just return 
    #the index as it is
    if (index_in_inode_table < 12):
       return index_in_inode_table
    #index in inode table can be a max of 14, giving a max level of indirect = 3
    level_of_indirection = index_in_inode_table - 11
    #Initial logical_offset is 11 since we're finding offset for indirect blocks
    logical_offset = 11
    #This helps calculate the total offset
    while(level_of_indirection > 0):
        #256 ptrs in each level of indirection, so we keep incrementally finding
        #total logical offset
        logical_offset += num_ptrs_in_current_block ** (level_of_indirection-1)
        #Decrement the level of indirection until it is 0 so we can calculate total
        #required offset
        level_of_indirection = level_of_indirection - 1
    return logical_offset

#Helps parse rows that are Inode entries in the CSV file
def parse_inode_row(row, hash_map):
    ''' Processs an entry in the CSV file corresponding to an Inode '''
    #Save/retrieve inode number
    inode_num = int(row[1])
    #This is a string, so don't typecast to int
    file_type = row[2]
    file_size = int(row[10])
    #for symbolic links with a short length (60 bytes or less) the i-node block pointer fields do 
    #not contain block numbers, and so should not be analyzed.
    #Don't process the blocks in this case, just return
    if file_type == 's' and file_size <= 60:
        return
    #Create variables/constants
    first_block_index = 12
    num_blocks_in_inode = 15
    #The column in the row where we start reading values of indirect blocks
    #Will use this to find level of indirection
    last_direct_pointer = first_block_index + num_blocks_in_inode - 4
    #Essentially, go through columns 13-27 inclusive for this row since these 
    #correspond to the 15 data blocks for this inode entry
    for i in range(first_block_index, first_block_index+num_blocks_in_inode):
        #Retrieve the value from the ith column and save it in b_num
        b_num = int(row[i])
        #See if the block is a valid block/used block
        #Otherwise we don't want to analyze it
        if b_num != 0:
            #For direct blocks
            if i < last_direct_pointer:
                insert_block_into_map(Block(b_num, inode_num, find_logical_offset(256, i - first_block_index), False), hash_map)
            #For indirect blocks, we also want to pass in the level of indirection into the constructor
            else:
                insert_block_into_map(Block(b_num, inode_num, find_logical_offset(256, i - first_block_index), False, i - 23), hash_map)

#Helps parse an indirect row entry in the CSV
def parse_indirect_row(row, hash_map):
    ''' Helper method to process an indirect block row in the CSV file '''
    #Save values from the row
    inode_num = int(row[1])
    level_of_indirection = int(row[2])
    #Parse logical offset as a long integer
    logical_offset = int(row[3])
    block_num_of_referenced = int(row[5])
    #Insert this block into the block hash_map
    insert_block_into_map(Block(block_num_of_referenced, inode_num, logical_offset, False, level_of_indirection), hash_map)

def parse_csv_block(row, hash_map):
    '''
    Essentially, this function parses every row to find data blocks, especially if the row 
    being analyzed relates to Inodes, free blocks or Indirect Blocks. It ignores reading 
    rows that correspond to superblocks, groups, directory entries and free inodes since 
    these are not required or may have already been processed.
    '''
    #Want to figure out whether the first element in the row is an INODE, INDIRECT BLOCK, FREE BLOCK
    #row[0] corresponds to the object in the file system that is being analyzed in that row
    #Want to use switch, but python doesn't have a straightforward switch statement
    #If it's either of these, we want to do nothing since we don't need to check/analyze them
    if row[0] == 'SUPERBLOCK' or row[0] == 'GROUP' or row[0] == 'DIRENT' or row[0] == 'IFREE':
        return
    #If the row is the row for an INODE, call helper method to parse the row
    elif row[0] == 'INODE':
        parse_inode_row(row, hash_map)
    #If the row is the row for an free block, call helper method to parse the row
    elif row[0] == 'BFREE':
        #int(row[1]) corresponds to the inode number
        insert_block_into_map( Block(int(row[1]), None, None, True), hash_map)
    #If the row is the row for an indirect block, call helper method to parse the row
    elif row[0] == 'INDIRECT':
        parse_indirect_row(row, hash_map)
    #At this point, we've exhausted all other possible entries in the CSV so this must 
    #be a mistake. Report this stderr and exit with status 1
    #This row should not be in the CSV file
    #Exit with code 1 since this CSV has bad parameters
    else:
        exit_1("ERROR: INVALID ROW NAME: " + row[0])
    pass

#Fill/Process all fields in the CSV file passed in during runtime
def fill_blocks(file_name):
    '''
    Read through all the rows in the CSV files and retrieve/save/store
    the required values
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
        #Can pass variables and expect values to updated correctly because python 
        #uses pointers internally and therefore automatically passes by reference
        for row in csv_reader:
            parse_csv_block(row, block_map)
        #Return the block map, along with the total number of blocks as an array
        return [block_map, super_info.total_num_blocks]

#One of the main functions to run a block audit as specified by the spec
def block_consistency_audits(file_name):
    '''
    This function runs a block consistency audit and writes to stdout if there are
    any seeming discrepancies in the blocks. 
    '''
    global check_for_discrepenacies
    #Want to get all the blocks from the CSV
    [block_hashmap, total_blocks] = fill_blocks(file_name)
    #The items() method returns a view object that displays a list of dictionary's (key, value) tuple pairs.
    for block_num, blocks in block_hashmap.items():
        #Variables need to keep track to see if a valid block has referenced by multiple files
        #and also if it appears on the free list
        free_block = 0
        alloc_block_count = 0
        #Each key can have multiple blocks in an array
        for block in blocks:
            #Every legal data block (every block between the end of the I-nodes and the start of the next 
            #group) should appear on on the free block list, or be allocated to exactly one file. 
            #If the block is used
            if not block.freeStatus():
                #An INVALID block is one whose number is less than zero or greater than the highest block in the file system.
                if not block.is_valid():
                    print("INVALID" + block.indirectionToString() + " BLOCK " + str(block.getNum()) + " IN INODE " + str(block.getInode()) + " AT OFFSET " + str(block.getOffset()))
                    check_for_discrepenacies = 1
                #A RESERVED block is one that could not legally be allocated to any file because it should be reserved for file system metadata
                elif block.isReserved():
                    print("RESERVED" + block.indirectionToString() + " BLOCK " + str(block.getNum()) + " IN INODE " + str(block.getInode()) + " AT OFFSET " + str(block.getOffset()))
                    check_for_discrepenacies = 1
                else:
                    #In this case, the block is valid, so we should keep a count of how many blocks
                    #of the same block_num we have that are valid
                    alloc_block_count += 1
                #A block that is allocated to some file might also appear on the free list. 
                if (free_block):
                    print("ALLOCATED BLOCK " + str(block.getNum()) + " ON FREELIST")
                    check_for_discrepenacies = 1
                    #Set this back to false
                    free_block = 0
            #If the block is free
            else:
                free_block = 1
        #If a legal block is referenced by multiple files, we want to print a duplicate mesasge
        #for every such legal reference
        if alloc_block_count > 1:
            for block in blocks:
                if block.is_valid() and not block.freeStatus() and not block.isReserved():
                    print("DUPLICATE" + block.indirectionToString() + " BLOCK " + str(block_num) + " IN INODE " + str(block.getInode()) + " AT OFFSET " + str(block.getOffset()))
                    check_for_discrepenacies = 1
    #Go through all the blocks. Since we collect block numbers from the indirect blocks, inodes and free lists,
    #any blocks that we haven't already collected have gone unreferenced, excluding the reserved blocks
    for i in range(0, total_blocks):
        #If the block is not in the array that we keep appending to in the Block class, as well in our 
        #current hashmap, then it is not referenced by any file and is not on the free list
        if i not in Block.reserved_blocks and i not in block_hashmap:
            print("UNREFERENCED BLOCK " + str(i))
            check_for_discrepenacies = 1

#Helper method to insert a given inode into a hashmap
def insert_inode_into_map(num, inode_hashmap, status):
    '''
    Helper method that inserts an allocate/unallocated inode entry
    from a given CSV file into an inode hashmap
    '''
    if num not in inode_hashmap:
        inode_hashmap[num] = [status]
    else:
        inode_hashmap[num].append(status)

#Helper method to process INODE entries in CSV file
def fill_inodes(file_name):
    '''
    Parses through the CSV to find all entries that pertain to inodes - 
    INODE and IFREE, and returns a list containing the hashmap, the first 
    inode and the total number of inodes.
    '''
    global inode_map_directory_copy
    global free_inode_list
    global inode_links
    with open(file_name) as csv_file:
        #Create a CSV reader object/iterable
        reader = csv.reader(csv_file, delimiter=",")
        super_block = process_superblock(reader)
        #Go back to the beginning of the CSV file
        csv_file.seek(0)
        inode_hashmap = {}
        #Go through all the rows in the CSV
        for row in reader:
            #0 - Unallocated/Free
            #1 - Allocated/Used
            inode_num = int(row[1])
            if row[0] == 'INODE':
                #Insert the following inode into our map
                insert_inode_into_map(inode_num, inode_hashmap, 1)
                #Save the link count for the given inode entry
                inode_links[inode_num] = int(row[6])
            elif row[0] == 'IFREE':
                #Insert the following inode into our map
                insert_inode_into_map(inode_num, inode_hashmap, 0)
                #Add this inode number to our free list so we can keep track of free inode numbers
                #Every unallocated I-Node should be on a free I-node list. 
                free_inode_list.append(inode_num)
            #We save a copy of our current hashmap globally
            inode_map_directory_copy = inode_hashmap
        #Return a list containing the hashmap, the first inode and the total number of inodes
        return [inode_hashmap, super_block.first_inode, super_block.total_num_inodes]

#Process Inode allocations and run an audit
def inode_allocation_audits(file_name):
    ''' Meaty helper function to audit inode entries in the CSV file. '''
    global check_for_discrepenacies
    global free_inode_list
    #Process all inode entries (INODE and IFREE) found in the CSV file
    [inode_map, first_inode, total_inodes] = fill_inodes(file_name)
    #Go through the key-value tuple returned by inode_map.items()
    for inode_num, inodes in inode_map.items():
        #Create member variables to save free and allocated count
        free_count = 0
        used_count = 0
        #Since the value of the key may have more than one inode in its list
        #The values in the list are either 1 (allocated) or 0 (unallocated)
        for inode in inodes:
            #Case where inode is unallocated
            if inode == 0:
                free_count += 1
            #Case where inode is allocated
            elif inode == 1:
                used_count += 1
        #See if there is an allocated inode with this inode_num
        #Need to check if both > 0, otherwise this inode is unused
        if used_count > 0 and free_count > 0:
            print("ALLOCATED INODE " + str(inode_num) + " ON FREELIST")
            free_inode_list.remove(inode_num)
            check_for_discrepenacies = 1
    #Now, go through all the inodes 
    #2 is the root directory (which we want to check for)
    for inode_num in ([2] + range(first_inode, total_inodes + 1)):
        if inode_num not in inode_map:
            print("UNALLOCATED INODE " + str(inode_num) + " NOT ON FREELIST")
            free_inode_list.append(inode_num)
            check_for_discrepenacies = 1

#Helper function to fill directories 
def fill_directories(file_name):
    '''
    Helper function to read DIRENT entries in the CSV file and parse the 
    information we need to verify if directory entries are consistent
    '''
    with open(file_name) as csv_file:
        #Create a reader iterable
        reader = csv.reader(csv_file, delimiter=",")
        super_block = process_superblock(reader)
        #Reset starting point of the file to the beginning
        csv_file.seek(0)
        #Create an array to push Directory objects if they're found in the CSV file
        directories = []
        #Go through all the rows in the CSV file
        for row in reader:
            if row[0] == 'DIRENT':
                #Initialize a directory object and append it to the directories array,
                #which will be returned by this function
                directories.append(Directory(row))
        return [directories, super_block.first_inode, super_block.total_num_inodes]

#Main function to run directory consistency audits
def directory_consistency_audits(file_name):
    '''
    Function to process directory entries in the CSV 
    '''
    global check_for_discrepenacies
    #Call helper method to retrieve directories 
    [directories, first_inode, total_inodes] = fill_directories(file_name)
    links = {}
    self_to_parent_inodes = {2: 2}
    for entry in directories:
        #An INVALID I-node is one whose number is less than 1 or greater than the last I-node in the system. 
        if entry.self_inode_num > total_inodes or entry.self_inode_num < 1:
            print("DIRECTORY INODE " + str(entry.parent_inode_num) + " NAME " + entry.file_name + " INVALID INODE " + str(entry.self_inode_num))
            check_for_discrepenacies = 1
        #For any reference to an invalid or unallocated I-node
        #Free_inode_list contains all unallocated inodes
        elif entry.self_inode_num in free_inode_list:
            print("DIRECTORY INODE " + str(entry.parent_inode_num) + " NAME " + entry.file_name + " UNALLOCATED INODE " + str(entry.self_inode_num))
            check_for_discrepenacies = 1
        else:
            #Find the inode number in links and increment its count by 1
            links[entry.self_inode_num] = links.get(entry.self_inode_num, 0) + 1
            #We process these later, since they require separate checking.
            #However, for that to work, we 
            if entry.file_name != "'.'" and entry.file_name != "'..'":
                self_to_parent_inodes[entry.self_inode_num] = entry.parent_inode_num

    #Trying to check if link counts match up 
    #Go through all the links in the dictionary
    for inode in inode_links:
        #We know the link count from when we scanned inodes
        count = inode_links[inode]
        #Go through all the links
        if inode in links:
            #If the above value is not equal to the links, then we write to stdout
            if count != links[inode]:
                print("INODE " + str(inode)+ " HAS " + str(links[inode]) + " LINKS BUT LINKCOUNT IS " + str(count))
                check_for_discrepenacies = 1
        #Otherwise the count must be 0 since there are no links. If this is not what is returned, write to stdout
        elif count != 0:
            print("INODE " + str(inode)+ " HAS 0 LINKS BUT LINKCOUNT IS " + str(count))
            check_for_discrepenacies = 1
    
    #Again, go through all the entries in the directories dictionary
    for entry in directories:
        #Special Case
        if entry.file_name == "'.'":
            if entry.parent_inode_num != entry.self_inode_num:
                print("DIRECTORY INODE " + str(entry.parent_inode_num) + " NAME '.' LINK TO INODE " + str(entry.self_inode_num) + " SHOULD BE " + str(entry.parent_inode_num))
                check_for_discrepenacies = 1
        #Special Case
        elif entry.file_name == "'..'":
            if entry.self_inode_num != self_to_parent_inodes[entry.parent_inode_num]:
                print("DIRECTORY INODE " + str(entry.parent_inode_num) + " NAME '..' LINK TO INODE " + str(entry.self_inode_num) + " SHOULD BE " + str(self_to_parent_inodes[entry.parent_inode_num]))
                check_for_discrepenacies = 1

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
    #Run block consistency audits
    block_consistency_audits(file_name)
    inode_allocation_audits(file_name)
    directory_consistency_audits(file_name)
    #If successful but with inconsistencies
    if (check_for_discrepenacies):
        sys.exit(2)
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