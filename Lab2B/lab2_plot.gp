#! /usr/bin/gnuplot
#
# purpose:
#	 generate data reduction graphs for the multi-threaded list project
#
# input: lab2_list.csv
#	1. test name
#	2. # threads
#	3. # iterations per thread
#	4. # lists
#	5. # operations performed (threads x iterations x (ins + lookup + delete))
#	6. run time (ns)
#	7. run time per operation (ns)
#       8. average wait for lock (ns)
#
# output:
#	lab2b_1.png ... Throughput vs Synchronization (Mutex and Spin-lock)
#	lab2b_2.png ... Avg. wait-for-lock time && Avg. time per operation vs Threads (Mutex)
#	lab2b_3.png ... Succesful iterations for synchronization methods
#	lab2b_4.png ... Compares performance of a paritioned list for mutex operations
#       lab2b_5.png ... Compares performance of a paritioned list for spinlock operations
#

#Define a variable that represents number of nanoseconds in a second
NS = 1000000000

# general plot parameters
set terminal png
set datafile separator ","

# Lab2B_1:
set title "Lab2B-1: Throughput vs Synchronization (Mutex and Spin-lock)"
set ylabel "Throughput"
set logscale y 10
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set output 'lab2b_1.png'
plot \
     "< grep -E \"list-none-m,[0-9]+,1000,1,\" lab2b_list.csv" using ($2):(NS/($7)) \
	title 'Mutex' with linespoints lc rgb 'red', \
     "< grep -E \"list-none-s,[0-9]+,1000,1,\" lab2b_list.csv" using ($2):(NS/($7)) \
	title 'Spin-lock' with linespoints lc rgb 'blue'

##############################################################################################

# Lab2B_2:
set title "Lab2B-2: Avg. wait-for-lock time && Avg. time per operation vs Threads (Mutex)"
set ylabel "Time"
set logscale y 10
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set output 'lab2b_2.png'
plot \
     "< grep -E \"list-none-m,[0-9]+,1000,1,\" lab2b_list.csv" using ($2):($8) \
	title 'Avg. wait-for-lock time' with linespoints lc rgb 'blue', \
     "< grep -E \"list-none-m,[0-9]+,1000,1,\" lab2b_list.csv" using ($2):($7) \
	title 'Avg. time per operation' with linespoints lc rgb 'red'

##############################################################################################

# Lab2B_3:
set title "Lab2B-3: Succesful iterations for synchronization methods"
set key right top
set ylabel "Successful Iterations"
set logscale y 10
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set output 'lab2b_3.png'
plot \
     "< grep -E \"list-id-none,[0-9]+,[0-9]+,4,\" lab2b_list.csv" using ($2):($3) \
	title 'Unprotected (no synchronization)' with points lc rgb 'blue', \
     "< grep -E \"list-id-m,[0-9]+,[0-9]+,4,\" lab2b_list.csv" using ($2):($3) \
	title 'Mutex Iterations' with points lc rgb 'green', \
     "< grep -E \"list-id-m,[0-9]+,[0-9]+,4,\" lab2b_list.csv" using ($2):($3) \
	title 'Spinlock Iterations' with points lc rgb 'red'

##############################################################################################

# Lab2B_4:
set title "Lab2B-4: Performance of a paritioned list for mutex operations"
set ylabel "Throughput"
set logscale y 10
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set output 'lab2b_4.png'
plot \
     "< grep -E \"list-none-m,[0-9],1000,1,|list-none-m,12,1000,1,\" lab2b_list.csv" using ($2):(NS/($7)) \
	title '1 list' with linespoints lc rgb 'orange', \
     "< grep -E \"list-none-m,[0-9],1000,4,|list-none-m,12,1000,4,\" lab2b_list.csv" using ($2):(NS/($7)) \
	title '4 lists' with linespoints lc rgb 'red', \
     "< grep -E \"list-none-m,[0-9],1000,8,|list-none-m,12,1000,8,\" lab2b_list.csv" using ($2):(NS/($7)) \
	title '8 lists' with linespoints lc rgb 'green', \
     "< grep -E \"list-none-m,[0-9],1000,16,|list-none-m,12,1000,16,\" lab2b_list.csv" using ($2):(NS/($7)) \
	title '16 lists' with linespoints lc rgb 'blue'

##############################################################################################

# Lab2B_5:
set title "Lab2B-5: Performance of a paritioned list for spinlock operations"
set ylabel "Throughput"
set logscale y 10
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set output 'lab2b_5.png'
plot \
     "< grep -E \"list-none-s,[0-9],1000,1,|list-none-s,12,1000,1,\" lab2b_list.csv" using ($2):(NS/($7)) \
	title '1 list' with linespoints lc rgb 'orange', \
     "< grep -E \"list-none-s,[0-9],1000,4,|list-none-s,12,1000,4,\" lab2b_list.csv" using ($2):(NS/($7)) \
	title '4 lists' with linespoints lc rgb 'red', \
     "< grep -E \"list-none-s,[0-9],1000,8,|list-none-s,12,1000,8,\" lab2b_list.csv" using ($2):(NS/($7)) \
	title '8 lists' with linespoints lc rgb 'green', \
     "< grep -E \"list-none-s,[0-9],1000,16,|list-none-s,12,1000,16,\" lab2b_list.csv" using ($2):(NS/($7)) \
	title '16 lists' with linespoints lc rgb 'blue'
