#NAME: Arnav Garg
#ID: 304911796
#EMAIL: arnavgrg@ucla.edu

.SILENT:

default:
	gcc -Wall -Wextra -g -lmraa -lm lab4b.c -o lab4b 

dist:
	tar -czf lab4b-304911796.tar.gz lab4b.c README Makefile tests.sh

clean:
	rm -rf lab4b *.tar.gz

check: default
	chmod +x tests.sh
	./tests.sh