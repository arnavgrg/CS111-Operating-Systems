    # ------------- start of lab2b_1.png tests ------------------- #
    #Spin-lock synchronized list operations
    ./lab2_list --threads=1  --iterations=1000 --sync=s > lab2b_list.csv
    ./lab2_list --threads=2  --iterations=1000 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=4  --iterations=1000 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=8  --iterations=1000 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2b_list.csv
    #Mutex Synchronized List Operations
    # ------------- start of lab2b_2.png tests ------------------- #
    ./lab2_list --threads=1  --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=2  --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=4  --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=8  --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2b_list.csv
    # ------------- end of lab2b_2.png tests ------------------- #
    # ------------- end of lab2b_1.png tests ------------------- #
    
    # ------------- start of lab2b_3.png tests ------------------- #
    #Without any synchronization
    #1 iteration
    ./lab2_list --threads=1  --lists=4 --yield=id >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id >> lab2b_list.csv
    #2 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=2 >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=2 >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=2 >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=2 >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=2 >> lab2b_list.csv
    #4 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=4 >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=4 >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=4 >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=4 >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=4 >> lab2b_list.csv
    #8 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=8 >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=8 >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=8 >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=8 >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=8 >> lab2b_list.csv
    #16 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=16 >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=16 >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=16 >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=16 >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=16 >> lab2b_list.csv
    #Same, but with spinlock
    #10 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=10 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=10 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=10 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=10 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=10 --sync=s >> lab2b_list.csv
    #20 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=20 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=20 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=20 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=20 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=20 --sync=s >> lab2b_list.csv
    #40 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=40 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=40 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=40 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=40 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=40 --sync=s >> lab2b_list.csv
    #80 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=80 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=80 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=80 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=80 --sync=s >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=80 --sync=s >> lab2b_list.csv
    #Same, but with mutex
    #10 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=10 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=10 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=10 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=10 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=10 --sync=m >> lab2b_list.csv
    #20 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=20 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=20 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=20 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=20 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=20 --sync=m >> lab2b_list.csv
    #40 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=40 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=40 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=40 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=40 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=40 --sync=m >> lab2b_list.csv
    #80 iterations
    ./lab2_list --threads=1  --lists=4 --yield=id --iterations=80 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=4  --lists=4 --yield=id --iterations=80 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=8  --lists=4 --yield=id --iterations=80 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=12 --lists=4 --yield=id --iterations=80 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=16 --lists=4 --yield=id --iterations=80 --sync=m >> lab2b_list.csv
    # ------------- end of lab2b_3.png tests ------------------- #
   