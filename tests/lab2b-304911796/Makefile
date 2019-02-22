#NAME: ARNAV GARG
#UID: 304911796
#EMAIL: arnavgrg@ucla.edu
#SLIPDAYS: 3

.SILENT:

default: build

build:
	gcc -g -Wall -Wextra -lpthread -lprofiler lab2_list.c SortedList.c -o lab2_list

clean:
	rm -rf lab2_list *.tar.gz *.o *.dSYM DS_Store

profile: build
	-rm -f ./raw.gperf 1>/dev/null 2>/dev/null
	-CPUPROFILE=./raw.gperf ./lab2_list --sync=s --threads=12 --iterations=1000 1>/dev/null 2>/dev/null
	-pprof --text ./lab2_list ./raw.gperf >profile.out 2>/dev/null
	-pprof --list=start_routine ./lab2_list ./raw.gperf >> profile.out 2>/dev/null
	-pprof --list=l_insert ./lab2_list ./raw.gperf >> profile.out 2>/dev/null
	-pprof --list=l_delete ./lab2_list ./raw.gperf >> profile.out 2>/dev/null
	rm -f ./raw.gperf 1>/dev/null 2>/dev/null

dist: graphs
	tar -czvf lab2b-304911796.tar.gz SortedList.* lab2_list.c Makefile README lab2b_list.csv lab2_plot.gp tests.sh *.png profile.out

graphs: tests 
	chmod +x lab2_plot.gp
	-gnuplot lab2_plot.gp

tests: build
	chmod +x tests.sh
	-./tests.sh
