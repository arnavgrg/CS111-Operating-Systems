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
	tar -czf lab1A-304911796.tar.gz simpsh.c Makefile README test.sh

check: default 
	./test.sh
	#need to add target: clean somehow after running test.sh shell script



