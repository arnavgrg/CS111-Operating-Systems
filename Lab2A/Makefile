#NAME: ARNAV GARG
#UID: 304911796
#EMAIL: arnavgrg@ucla.edu
#SLIPDAYS: 3

.SILENT:

all: build

build:
	gcc -g -Wall -Wextra -lpthread lab2_add.c -o lab2_add 
	gcc -g -Wall -Wextra -lpthread lab2_list.c -o lab2_list SortedList.c

clean:
	rm -rf lab2_add lab2_list lab2a-304911796.tar.gz *.o

dist: graphs
	tar -czvf lab2a-304911796.tar.gz lab2_add.c SortedList.h SortedList.c lab2_list.c Makefile README lab2_add.csv lab2_list.csv lab2_add-1.png lab2_add-2.png lab2_add-3.png lab2_add-4.png lab2_add-5.png lab2_list-1.png lab2_list-2.png lab2_list-3.png lab2_list-4.png lab2_list.gp lab2_add.gp tests.sh

graphs: tests 
	chmod +x lab2_add.gp
	chmod +x lab2_list.gp
	-gnuplot lab2_add.gp 
	-gnuplot lab2_list.gp

tests: build
	chmod +x tests.sh
	-./tests.sh