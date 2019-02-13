#NAME: ARNAV GARG
#UID: 304911796
#EMAIL ID: arnavgrg@ucla.edu
#SLIPDAYS: 1

.SILENT:

build:
	#Add -pthread flag to prevent undefined reference to pthread_create error in Linux
	gcc -g -Wall -Wextra -lpthread lab2_add.c -o lab2_add 
	gcc -g -Wall -Wextra -lpthread lab2_list.c -o lab2_list SortedList.c

clean:
	rm -rf lab2_add lab2_list *.tar.gz *.o *.txt *.png

dist:
	tar -czf lab2A-304911796.tar.gz lab2_add.c SortedList.h SortedList.c lab2_list.c Makefile README lab2_add.csv lab2_list.csv lab2_add-1.png lab2_add-2.png lab2_add-3.png lab2_add-4.png lab2_add-5.png lab2_list-1.png lab2_list-2.png lab2_list-3.png lab2_list-4.png

graphs: 
	gnuplot lab2_add.gp
	#gnuplot lab2_list.gp

tests: build
	# ---------------- For lab2_add.c -------------------- #
	#For 100 iterations, add-none
	./lab2_add --iterations=100 --threads=1 > lab2_add.csv
	./lab2_add --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=3 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=5 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=6 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=7 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=16 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=32 >> lab2_add.csv
	#For 1000 iterations, add-none
	./lab2_add --iterations=1000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=3 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=5 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=6 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=7 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=16 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=32 >> lab2_add.csv
	#For 10000 iterations, add-none
	./lab2_add --iterations=10000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=3 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=5 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=6 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=7 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=16 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=32 >> lab2_add.csv
	#For 100000 iterations, add-none
	./lab2_add --iterations=100000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=100000 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=100000 --threads=3 >> lab2_add.csv
	./lab2_add --iterations=100000 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=100000 --threads=5 >> lab2_add.csv
	./lab2_add --iterations=100000 --threads=6 >> lab2_add.csv
	./lab2_add --iterations=100000 --threads=7 >> lab2_add.csv
	./lab2_add --iterations=100000 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=100000 --threads=16 >> lab2_add.csv
	./lab2_add --iterations=100000 --threads=32 >> lab2_add.csv
	#For --yield flag, 2 threads
	./lab2_add --yield --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=40 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=100000 --threads=2 >> lab2_add.csv
	#For --yield flag, 4 threads
	./lab2_add --yield --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=40 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=100000 --threads=4 >> lab2_add.csv
	#For --yield flag, 8 threads
	./lab2_add --yield --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=40 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=100000 --threads=8 >> lab2_add.csv
	#For --yield flag, 12 threads
	./lab2_add --yield --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=40 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=100000 --threads=12 >> lab2_add.csv
	
	# ------------- start of lab2_add-3.png tests ------------------- #
	#For a single thread, how increase in iterations changes avg 
	#time per operation non-yield
	./lab2_add --iterations=10 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=20 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=50 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=250 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=500 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=750 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=2500 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=5000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=7500 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=25000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=50000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=75000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=100000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=250000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=500000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=750000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=1000000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=2500000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=5000000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=7500000 --threads=1 >> lab2_add.csv
	# ------------- end of lab2_add-3.png tests ------------------- #
	
	# ------------- start of lab2_add-4.png tests ------------------- #
	#For --yield flag, 2 threads, no synchronization options
	./lab2_add --yield --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=40 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=25000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=50000 --threads=2 >> lab2_add.csv
	#For --yield flag, 2 threads, mutexes
	./lab2_add --yield --sync=m --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=250 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=2500 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=10000 --threads=2 >> lab2_add.csv
	#For --yield flag, 2 threads, CAS
	./lab2_add --yield --sync=c --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=250 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=2500 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=10000 --threads=2 >> lab2_add.csv
	#For --yield flag, 2 threads, spin
	./lab2_add --yield --sync=s --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=250 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=750 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=1000 --threads=2 >> lab2_add.csv
	#For --yield flag, 4 threads, no synchronization options
	./lab2_add --yield --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=40 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=25000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=50000 --threads=4 >> lab2_add.csv
	#For --yield flag, 4 threads, mutexes
	./lab2_add --yield --sync=m --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=250 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=2500 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=10000 --threads=4 >> lab2_add.csv
	#For --yield flag, 4 threads, CAS
	./lab2_add --yield --sync=c --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=250 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=2500 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=10000 --threads=4 >> lab2_add.csv
	#For --yield flag, 4 threads, spin
	./lab2_add --yield --sync=s --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=250 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=750 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=1000 --threads=4 >> lab2_add.csv
	#For --yield flag, 8 threads, no synchronization options
	./lab2_add --yield --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=40 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=25000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=50000 --threads=8 >> lab2_add.csv
	#For --yield flag, 8 threads, mutexes
	./lab2_add --yield --sync=m --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=250 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=2500 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=10000 --threads=8 >> lab2_add.csv
	#For --yield flag, 8 threads, CAS
	./lab2_add --yield --sync=c --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=250 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=2500 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=10000 --threads=8 >> lab2_add.csv
	#For --yield flag, 8 threads, spin
	./lab2_add --yield --sync=s --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=250 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=750 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=1000 --threads=8 >> lab2_add.csv
	#For --yield flag, 12 threads, no synchronization options
	./lab2_add --yield --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=40 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=25000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=50000 --threads=12 >> lab2_add.csv
	#For --yield flag, 12 threads, mutexes
	./lab2_add --yield --sync=m --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=250 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=2500 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=10000 --threads=12 >> lab2_add.csv
	#For --yield flag, 12 threads, CAS
	./lab2_add --yield --sync=c --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=250 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=2500 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=10000 --threads=12 >> lab2_add.csv
	#For --yield flag, 12 threads, spin
	./lab2_add --yield --sync=s --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=250 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=750 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=1000 --threads=12 >> lab2_add.csv
	# ------------- end of lab2_add-4.png tests ------------------- #
	
	# ------------- start of lab2_add-5.png tests ------------------- #
	#For no flags, 1 thread
	./lab2_add --iterations=10 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=20 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=40 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=80 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=5000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=25000 --threads=1 >> lab2_add.csv
	./lab2_add --iterations=50000 --threads=1 >> lab2_add.csv
	#For 1 thread, mutexes
	./lab2_add --sync=m --iterations=10 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=20 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=50 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=100 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=250 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=500 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=1000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=2500 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=5000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=10000 --threads=1 >> lab2_add.csv
	#For 1 thread, CAS
	./lab2_add --sync=c --iterations=10 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=20 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=50 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=100 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=250 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=500 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=1000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=2500 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=5000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=10000 --threads=1 >> lab2_add.csv
	#For 1 thread, spin
	./lab2_add --sync=s --iterations=10 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=20 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=50 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=100 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=250 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=500 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=750 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=1000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=5000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=10000 --threads=1 >> lab2_add.csv
	#For no flags, threads=2 
	./lab2_add --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=40 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=80 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=25000 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=50000 --threads=2 >> lab2_add.csv
	#For 2 threads, mutexes
	./lab2_add --sync=m --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=250 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=2500 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=10000 --threads=2 >> lab2_add.csv
	#For 2 threads, CAS
	./lab2_add --sync=c --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=250 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=2500 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=10000 --threads=2 >> lab2_add.csv
	#For 2 threads, spin
	./lab2_add --sync=s --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=250 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=750 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=10000 --threads=2 >> lab2_add.csv
	#For no flags, threads=4
	./lab2_add --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=40 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=80 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=25000 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=50000 --threads=4 >> lab2_add.csv
	#For 4 threads, mutexes
	./lab2_add --sync=m --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=250 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=2500 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=10000 --threads=4 >> lab2_add.csv
	#For 4 threads, CAS
	./lab2_add --sync=c --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=250 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=2500 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=10000 --threads=4 >> lab2_add.csv
	#For 4 threads, spin
	./lab2_add --sync=s --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=250 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=750 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=10000 --threads=4 >> lab2_add.csv
	#For no flags, threads=8
	./lab2_add --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=40 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=80 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=25000 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=50000 --threads=8 >> lab2_add.csv
	#For 8 threads, mutexes
	./lab2_add --sync=m --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=250 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=2500 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=10000 --threads=8 >> lab2_add.csv
	#For 8 threads, CAS
	./lab2_add --sync=c --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=250 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=2500 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=10000 --threads=8 >> lab2_add.csv
	#For 8 threads, spin
	./lab2_add --sync=s --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=250 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=750 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=10000 --threads=8 >> lab2_add.csv
	#For no flags, threads=12 
	./lab2_add --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=40 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=80 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=25000 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=50000 --threads=12 >> lab2_add.csv
	#For 12 threads, mutexes
	./lab2_add --sync=m --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=250 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=2500 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=10000 --threads=12 >> lab2_add.csv
	#For 12 threads, CAS
	./lab2_add --sync=c --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=250 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=2500 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=10000 --threads=12 >> lab2_add.csv
	#For 12 threads, spin
	./lab2_add --sync=s --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=250 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=750 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=10000 --threads=12 >> lab2_add.csv
	# ------------- end of lab2_add-5.png tests ------------------- #
	make clean