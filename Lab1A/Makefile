#
#Name: Arnav Garg
#Email: arnavgrg@ucla.edu
#UID: 304911796
#
.SILENT: 

default:
	gcc simpsh.c -o simpsh

clean:
	rm -rf simpsh *.txt *.tar.gz *.o

dist:
	tar -czf lab1-304911796.tar.gz simpsh.c Makefile README test.sh

check: default test1 clean

test1: 
	echo "This is test 1" > input.txt; \
	echo | ./simpsh --rdonly input.txt &> /dev/null; \
	if [[ $$? -eq 0 ]]; then \
		echo "Test1 Passed: rdonly works correctly" \
	else \
		echo "Test1 Failed: rdonly does not work;" \
	fi
	



