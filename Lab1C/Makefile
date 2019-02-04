#
#NAME: Arnav Garg
#EMAIL ID: arnavgrg@ucla.edu
#UID: 304911796
#
.SILENT: 

default:
	gcc -g simpsh.c -o simpsh; 

clean:
	rm -rf simpsh *.tar.gz *.o

dist:
	tar -czf lab1-304911796.tar.gz simpsh.c Makefile README

check: test 

test: 
	./test.sh