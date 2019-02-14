#NAME: ARNAV GARG
#UID: 304911796
#EMAIL ID: arnavgrg@ucla.edu
#SLIPDAYS: 2

.SILENT:

build:
	#Add -pthread flag to prevent undefined reference to pthread_create error in Linux
	gcc -g -Wall -Wextra -lpthread lab2_add.c -o lab2_add 
	gcc -g -Wall -Wextra -lpthread lab2_list.c -o lab2_list SortedList.c

clean:
	rm -rf lab2_add lab2_list *.tar.gz *.o *.txt *.png

dist:
	tar -czf lab2a-304911796.tar.gz lab2_add.c SortedList.h SortedList.c lab2_list.c Makefile README lab2_add.csv lab2_list.csv lab2_add-1.png lab2_add-2.png lab2_add-3.png lab2_add-4.png lab2_add-5.png lab2_list-1.png lab2_list-2.png lab2_list-3.png lab2_list-4.png

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
	./lab2_add --yield --iterations=40 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --iterations=50000 --threads=2 >> lab2_add.csv
	#For --yield flag, 2 threads, mutexes
	./lab2_add --yield --sync=m --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=10000 --threads=2 >> lab2_add.csv
	#For --yield flag, 2 threads, CAS
	./lab2_add --yield --sync=c --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=10000 --threads=2 >> lab2_add.csv
	#For --yield flag, 2 threads, spin
	./lab2_add --yield --sync=s --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=20 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=1000 --threads=2 >> lab2_add.csv
	#For --yield flag, 4 threads, no synchronization options
	./lab2_add --yield --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=40 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --iterations=50000 --threads=4 >> lab2_add.csv
	#For --yield flag, 4 threads, mutexes
	./lab2_add --yield --sync=m --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=10000 --threads=4 >> lab2_add.csv
	#For --yield flag, 4 threads, CAS
	./lab2_add --yield --sync=c --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=10000 --threads=4 >> lab2_add.csv
	#For --yield flag, 4 threads, spin
	./lab2_add --yield --sync=s --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=20 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=1000 --threads=4 >> lab2_add.csv
	#For --yield flag, 8 threads, no synchronization options
	./lab2_add --yield --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=40 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --iterations=50000 --threads=8 >> lab2_add.csv
	#For --yield flag, 8 threads, mutexes
	./lab2_add --yield --sync=m --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=10000 --threads=8 >> lab2_add.csv
	#For --yield flag, 8 threads, CAS
	./lab2_add --yield --sync=c --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=10000 --threads=8 >> lab2_add.csv
	#For --yield flag, 8 threads, spin
	./lab2_add --yield --sync=s --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=20 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=1000 --threads=8 >> lab2_add.csv
	#For --yield flag, 12 threads, no synchronization options
	./lab2_add --yield --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=40 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=80 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=10000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --iterations=50000 --threads=12 >> lab2_add.csv
	#For --yield flag, 12 threads, mutexes
	./lab2_add --yield --sync=m --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=m --iterations=10000 --threads=12 >> lab2_add.csv
	#For --yield flag, 12 threads, CAS
	./lab2_add --yield --sync=c --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=c --iterations=10000 --threads=12 >> lab2_add.csv
	#For --yield flag, 12 threads, spin
	./lab2_add --yield --sync=s --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=20 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --yield --sync=s --iterations=500 --threads=12 >> lab2_add.csv
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
	./lab2_add --iterations=50000 --threads=1 >> lab2_add.csv
	#For 1 thread, mutexes
	./lab2_add --sync=m --iterations=10 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=20 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=50 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=100 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=500 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=1000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=5000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=m --iterations=10000 --threads=1 >> lab2_add.csv
	#For 1 thread, CAS
	./lab2_add --sync=c --iterations=10 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=50 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=100 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=500 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=1000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=5000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=c --iterations=10000 --threads=1 >> lab2_add.csv
	#For 1 thread, spin
	./lab2_add --sync=s --iterations=10 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=50 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=100 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=500 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=1000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=5000 --threads=1 >> lab2_add.csv
	./lab2_add --sync=s --iterations=10000 --threads=1 >> lab2_add.csv
	#For no flags, threads=2 
	./lab2_add --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=40 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=80 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=2 >> lab2_add.csv
	./lab2_add --iterations=50000 --threads=2 >> lab2_add.csv
	#For 2 threads, mutexes
	./lab2_add --sync=m --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=m --iterations=10000 --threads=2 >> lab2_add.csv
	#For 2 threads, CAS
	./lab2_add --sync=c --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=c --iterations=10000 --threads=2 >> lab2_add.csv
	#For 2 threads, spin
	./lab2_add --sync=s --iterations=10 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=50 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=100 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=500 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=1000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=5000 --threads=2 >> lab2_add.csv
	./lab2_add --sync=s --iterations=10000 --threads=2 >> lab2_add.csv
	#For no flags, threads=4
	./lab2_add --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=40 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=80 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=4 >> lab2_add.csv
	./lab2_add --iterations=50000 --threads=4 >> lab2_add.csv
	#For 4 threads, mutexes
	./lab2_add --sync=m --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=m --iterations=10000 --threads=4 >> lab2_add.csv
	#For 4 threads, CAS
	./lab2_add --sync=c --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=c --iterations=10000 --threads=4 >> lab2_add.csv
	#For 4 threads, spin
	./lab2_add --sync=s --iterations=10 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=50 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=100 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=500 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=1000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=5000 --threads=4 >> lab2_add.csv
	./lab2_add --sync=s --iterations=10000 --threads=4 >> lab2_add.csv
	#For no flags, threads=8
	./lab2_add --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=40 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=80 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=8 >> lab2_add.csv
	./lab2_add --iterations=50000 --threads=8 >> lab2_add.csv
	#For 8 threads, mutexes
	./lab2_add --sync=m --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=m --iterations=10000 --threads=8 >> lab2_add.csv
	#For 8 threads, CAS
	./lab2_add --sync=c --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=c --iterations=10000 --threads=8 >> lab2_add.csv
	#For 8 threads, spin
	./lab2_add --sync=s --iterations=10 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=50 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=100 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=500 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=1000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=5000 --threads=8 >> lab2_add.csv
	./lab2_add --sync=s --iterations=10000 --threads=8 >> lab2_add.csv
	#For no flags, threads=12 
	./lab2_add --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=40 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=80 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=10000 --threads=12 >> lab2_add.csv
	./lab2_add --iterations=50000 --threads=12 >> lab2_add.csv
	#For 12 threads, mutexes
	./lab2_add --sync=m --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=m --iterations=10000 --threads=12 >> lab2_add.csv
	#For 12 threads, CAS
	./lab2_add --sync=c --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=c --iterations=10000 --threads=12 >> lab2_add.csv
	#For 12 threads, spin
	./lab2_add --sync=s --iterations=10 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=50 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=100 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=500 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=1000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=5000 --threads=12 >> lab2_add.csv
	./lab2_add --sync=s --iterations=10000 --threads=12 >> lab2_add.csv
	# ------------- end of lab2_add-5.png tests ------------------- #


	# ------------- start of lab2_list-1.png tests ------------------- #
	./lab2_list --iterations=10 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=50 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=100 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=500 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=5000 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=10000 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=15000 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=20000 --threads=1 >> lab2_list.csv
	# ------------- end of lab2_list-1.png tests ------------------- #


	# ------------- start of lab2_list-1.png tests ------------------- #
	./lab2_list --iterations=10 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=100 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=5000 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=10000 --threads=1 >> lab2_list.csv
	./lab2_list --iterations=20000 --threads=1 >> lab2_list.csv
	# ------------- end of lab2_list-1.png tests ------------------- #

	
	# ------------- start of lab2_list-2.png tests ------------------- #
	#2 Threads
	./lab2_list --threads=2 >> lab2_list.csv
	./lab2_list --iterations=10 --threads=2 >> lab2_list.csv
	./lab2_list --iterations=100 --threads=2 >> lab2_list.csv
	./lab2_list --iterations=500 --threads=2 >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=2 >> lab2_list.csv
	#4 Threads
	./lab2_list --threads=4 >> lab2_list.csv
	./lab2_list --iterations=10 --threads=4 >> lab2_list.csv
	./lab2_list --iterations=100 --threads=4 >> lab2_list.csv
	./lab2_list --iterations=500 --threads=4 >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=4 >> lab2_list.csv
	#8 Threads
	./lab2_list --threads=8 >> lab2_list.csv
	./lab2_list --iterations=10 --threads=8 >> lab2_list.csv
	./lab2_list --iterations=100 --threads=8 >> lab2_list.csv
	./lab2_list --iterations=500 --threads=8 >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=8 >> lab2_list.csv
	#12 Threads
	./lab2_list --threads=12 >> lab2_list.csv
	./lab2_list --iterations=10 --threads=12 >> lab2_list.csv
	./lab2_list --iterations=100 --threads=12 >> lab2_list.csv
	./lab2_list --iterations=500 --threads=12 >> lab2_list.csv
	./lab2_list --iterations=1000 --threads=12 >> lab2_list.csv
	#2 Threads + yield=i
	./lab2_list --yield=i --threads=2 >> lab2_list.csv
	./lab2_list --yield=i --iterations=2 --threads=2 >> lab2_list.csv
	./lab2_list --yield=i --iterations=4 --threads=2 >> lab2_list.csv
	./lab2_list --yield=i --iterations=8 --threads=2 >> lab2_list.csv
	./lab2_list --yield=i --iterations=16 --threads=2 >> lab2_list.csv
	./lab2_list --yield=i --iterations=32 --threads=2 >> lab2_list.csv
	#4 Threads + yield=i
	./lab2_list --yield=i --threads=4 >> lab2_list.csv
	./lab2_list --yield=i --iterations=2 --threads=4 >> lab2_list.csv
	./lab2_list --yield=i --iterations=4 --threads=4 >> lab2_list.csv
	./lab2_list --yield=i --iterations=8 --threads=4 >> lab2_list.csv
	./lab2_list --yield=i --iterations=16 --threads=4 >> lab2_list.csv
	./lab2_list --yield=i --iterations=32 --threads=4 >> lab2_list.csv
	#8 Threads + yield=i
	./lab2_list --yield=i --threads=8 >> lab2_list.csv
	./lab2_list --yield=i --iterations=2 --threads=8 >> lab2_list.csv
	./lab2_list --yield=i --iterations=4 --threads=8 >> lab2_list.csv
	./lab2_list --yield=i --iterations=8 --threads=8 >> lab2_list.csv
	./lab2_list --yield=i --iterations=16 --threads=8 >> lab2_list.csv
	./lab2_list --yield=i --iterations=32 --threads=8 >> lab2_list.csv
	#12 Threads + yield=i
	./lab2_list --yield=i --threads=12 >> lab2_list.csv
	./lab2_list --yield=i --iterations=2 --threads=12 >> lab2_list.csv
	./lab2_list --yield=i --iterations=4 --threads=12 >> lab2_list.csv
	./lab2_list --yield=i --iterations=8 --threads=12 >> lab2_list.csv
	./lab2_list --yield=i --iterations=16 --threads=12 >> lab2_list.csv
	./lab2_list --yield=i --iterations=32 --threads=12 >> lab2_list.csv
	#2 Threads + yield=d
	./lab2_list --yield=d --threads=2 >> lab2_list.csv
	./lab2_list --yield=d --iterations=2 --threads=2 >> lab2_list.csv
	./lab2_list --yield=d --iterations=4 --threads=2 >> lab2_list.csv
	./lab2_list --yield=d --iterations=8 --threads=2 >> lab2_list.csv
	./lab2_list --yield=d --iterations=16 --threads=2 >> lab2_list.csv
	./lab2_list --yield=d --iterations=32 --threads=2 >> lab2_list.csv
	#4 Threads + yield=d
	./lab2_list --yield=d --threads=4 >> lab2_list.csv
	./lab2_list --yield=d --iterations=2 --threads=4 >> lab2_list.csv
	./lab2_list --yield=d --iterations=4 --threads=4 >> lab2_list.csv
	./lab2_list --yield=d --iterations=8 --threads=4 >> lab2_list.csv
	./lab2_list --yield=d --iterations=16 --threads=4 >> lab2_list.csv
	./lab2_list --yield=d --iterations=32 --threads=4 >> lab2_list.csv
	#8 Threads + yield=d
	./lab2_list --yield=d --threads=8 >> lab2_list.csv
	./lab2_list --yield=d --iterations=2 --threads=8 >> lab2_list.csv
	./lab2_list --yield=d --iterations=4 --threads=8 >> lab2_list.csv
	./lab2_list --yield=d --iterations=8 --threads=8 >> lab2_list.csv
	./lab2_list --yield=d --iterations=16 --threads=8 >> lab2_list.csv
	./lab2_list --yield=d --iterations=32 --threads=8 >> lab2_list.csv
	#12 Threads + yield=d
	./lab2_list --yield=d --threads=12 >> lab2_list.csv
	./lab2_list --yield=d --iterations=2 --threads=12 >> lab2_list.csv
	./lab2_list --yield=d --iterations=4 --threads=12 >> lab2_list.csv
	./lab2_list --yield=d --iterations=8 --threads=12 >> lab2_list.csv
	./lab2_list --yield=d --iterations=16 --threads=12 >> lab2_list.csv
	./lab2_list --yield=d --iterations=32 --threads=12 >> lab2_list.csv
	#2 Threads + yield=il
	./lab2_list --yield=il --threads=2 >> lab2_list.csv
	./lab2_list --yield=il --iterations=2 --threads=2 >> lab2_list.csv
	./lab2_list --yield=il --iterations=4 --threads=2 >> lab2_list.csv
	./lab2_list --yield=il --iterations=8 --threads=2 >> lab2_list.csv
	./lab2_list --yield=il --iterations=16 --threads=2 >> lab2_list.csv
	./lab2_list --yield=il --iterations=32 --threads=2 >> lab2_list.csv
	#4 Threads + yield=il
	./lab2_list --yield=il --threads=4 >> lab2_list.csv
	./lab2_list --yield=il --iterations=2 --threads=4 >> lab2_list.csv
	./lab2_list --yield=il --iterations=4 --threads=4 >> lab2_list.csv
	./lab2_list --yield=il --iterations=8 --threads=4 >> lab2_list.csv
	./lab2_list --yield=il --iterations=16 --threads=4 >> lab2_list.csv
	./lab2_list --yield=il --iterations=32 --threads=4 >> lab2_list.csv
	#8 Threads + yield=il
	./lab2_list --yield=il --threads=8 >> lab2_list.csv
	./lab2_list --yield=il --iterations=2 --threads=8 >> lab2_list.csv
	./lab2_list --yield=il --iterations=4 --threads=8 >> lab2_list.csv
	./lab2_list --yield=il --iterations=8 --threads=8 >> lab2_list.csv
	./lab2_list --yield=il --iterations=16 --threads=8 >> lab2_list.csv
	./lab2_list --yield=il --iterations=32 --threads=8 >> lab2_list.csv
	#12 Threads + yield=il
	./lab2_list --yield=il --threads=12 >> lab2_list.csv
	./lab2_list --yield=il --iterations=2 --threads=12 >> lab2_list.csv
	./lab2_list --yield=il --iterations=4 --threads=12 >> lab2_list.csv
	./lab2_list --yield=il --iterations=8 --threads=12 >> lab2_list.csv
	./lab2_list --yield=il --iterations=16 --threads=12 >> lab2_list.csv
	./lab2_list --yield=il --iterations=32 --threads=12 >> lab2_list.csv
	#2 Threads + yield=dl
	./lab2_list --yield=dl --threads=2 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=2 --threads=2 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=4 --threads=2 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=8 --threads=2 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=16 --threads=2 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=32 --threads=2 >> lab2_list.csv
	#4 Threads + yield=dl
	./lab2_list --yield=dl --threads=4 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=2 --threads=4 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=4 --threads=4 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=8 --threads=4 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=16 --threads=4 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=32 --threads=4 >> lab2_list.csv
	#8 Threads + yield=dl
	./lab2_list --yield=dl --threads=8 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=2 --threads=8 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=4 --threads=8 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=8 --threads=8 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=16 --threads=8 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=32 --threads=8 >> lab2_list.csv
	#12 Threads + yield=dl
	./lab2_list --yield=dl --threads=12 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=2 --threads=12 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=4 --threads=12 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=8 --threads=12 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=16 --threads=12 >> lab2_list.csv
	./lab2_list --yield=dl --iterations=32 --threads=12 >> lab2_list.csv
	# ------------- end of lab2_list-2.png tests ------------------- #

	make clean