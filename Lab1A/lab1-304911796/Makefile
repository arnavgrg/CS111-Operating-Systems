#
#NAME: Arnav Garg
#EMAIL ID: arnavgrg@ucla.edu
#UID: 304911796
#
.SILENT: 

default:
	gcc -g simpsh.c -o simpsh; 

clean:
	rm -rf simpsh *.txt *.tar.gz *.o

dist:
	tar -czf lab1-304911796.tar.gz simpsh.c Makefile README

check: default test1 test2 test3 test4

test1: 
	echo "This is test 1" > input.txt; \
	echo | ./simpsh --rdonly input.txt &> /dev/null; \
	if [[ $$? -eq 0 ]]; then \
		echo "Test1 Passed: rdonly works correctly."; \
	else \
		echo "Test1 Failed: rdonly does not work."; \
	fi

test2: 
	touch output.txt; \
	echo | ./simpsh --wronly output.txt &> /dev/null; \
	if [[ $$? -eq 0 ]]; then \
		echo "Test2 Passed: wronly works correctly."; \
	else \
		echo "Test2 Failed: wronly does not work."; \
	fi 

test3: 
	touch err.txt; \
	echo | ./simpsh --rdonly input.txt --wronly output.txt --wronly err.txt --command 0 1 2 cat; \
	if [[ $$? -eq 0 ]]; then \
		echo "Test3 Passed: command works successfully"; \
	else \
		echo "Test3 Failed: command does not work."; \
	fi 

test4:
	cmp input.txt output.txt &> /dev/null; \
	if [[ $$? -eq 0 ]]; then \
		echo "Test4 Passed: input and output redirection works as input.txt matches output.txt"; \
	else \
		echo "Test4 Failed: input and output redirection fails as input.txt and output.txt are not equal."; \
	fi
	rm -f input.txt output.txt err.txt