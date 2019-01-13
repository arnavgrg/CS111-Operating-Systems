# NAME: Arnav Garg
# EMAIL: arnavgrg@ucla.edu
# UID: 304911796

#Silent ensures comments and actual line of code being executed
#is not printed to stdout
.SILENT:

default:
	#Creates executable with debugging symbol table information
	#-Wall and -Wextra maximize compile-time error checking
	#-Wall : 
	#-Wextra : 
	gcc -Wall -Wextra -g lab0.c -o lab0

clean:
	#Remove all text and object files, the executable and compressed tarball
	rm -rf lab0 *.txt *.tar.gz *.o

dist: 
	#Creates the desired distribution (the actual compressed tarball zip)
	tar -czf lab0-304911796.tar.gz lab0.c Makefile backtrace.png breakpoint.png README

check: default test1 test2 test3 test4 test5 test6 clean
	#Builds executable and runs smoke tests
	#clean target added to ensure removal of any .txt, .o or executables created
	
test1:
	#Testing for incorrect flags/bad flags/bad arguments
	echo | ./lab0 --test1 hello --test2 world &> /dev/null; \
	if [[ $$? -ne 1 ]]; then \
		echo "TEST1 FAILED: incorrect argument returns wrong exit code $$?; Expected exit code 1"; \
	else \
		echo "TEST1 PASSED: incorrect argument returns exit code 1"; \
	fi

test2: 
	#Compare text to make sure both input and output are the same
	echo "This is a test string" > input.txt; \
	echo | ./lab0 --input input.txt --output output.txt &> /dev/null; \
	cmp input.txt output.txt; \
	if [[ $$? -eq 0 ]]; then \
		echo "TEST2 PASSED: output text matches input text"; \
	else \
		echo "TEST2 FAILED: output text does not match input text"; \
	fi 
	rm -f input.txt output.txt

test3: 
	#Test to ensure that lack of an argument for an input string causes an error
	echo | ./lab0 --input input.txt &> /dev/null; \
	if [[ $$? -eq 2 ]]; then \
		echo "TEST3 PASSED: Returns status 2 for missing input file"; \
	else \
		echo "TEST3 FAILED: Returns error code $$? despite missing input file"; \
	fi 

test4: 
	#Test to ensure output file is truncated before text from stdin is
	#written to stdout.
	echo "This is a test string" > output.txt; \
	echo "This is a string from input.txt" > input.txt; \
	echo | ./lab0 --input input.txt --output output.txt &> /dev/null; \
	cmp input.txt output.txt; \
	if [[ $$? -eq 0 ]]; then \
		echo "TEST4 PASSED: output text truncated and is same as input text"; \
	else \
		echo "TEST4 FAILED: output text does not match input text"; \
	fi 
	rm input.txt output.txt

test5:
	#See if segfault is created correctly
	echo | ./lab0 --segfault &> /dev/null; \
	if [[ $$? -eq 139 ]]; then \
		echo "TEST5 PASSED: Creation of segfault returns correct exit code"; \
	else \
		echo "TEST5 FAILED: Segfault returns wrong exit code"; \
	fi

test6:
	#Catch segfault after setting up a segfault handler
	echo | ./lab0 --catch --segfault &> /dev/null; \
	if [[ $$? -ne 4 ]]; then \
		echo "TEST6 FAILED: seg fault catch returns wrong exit code"; \
	else \
		echo "TEST6 PASSED: catch returns expected exit code 4"; \
	fi
