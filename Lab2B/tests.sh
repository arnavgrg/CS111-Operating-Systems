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
    ./lab2_list --threads=1  --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=2  --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=4  --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=8  --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2b_list.csv
    ./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2b_list.csv
    # ------------- end of lab2b_1.png tests ------------------- #
    
    
    # # ------------- start of lab2_list-1.png tests ------------------- #
    # ./lab2_list --iterations=10 --threads=1 >> lab2_list.csv
    # ./lab2_list --iterations=100 --threads=1 >> lab2_list.csv
    # ./lab2_list --iterations=1000 --threads=1 >> lab2_list.csv
    # ./lab2_list --iterations=10000 --threads=1 >> lab2_list.csv
    # ./lab2_list --iterations=20000 --threads=1 >> lab2_list.csv
    # # ------------- end of lab2_list-1.png tests ------------------- #

    
    # # ------------- start of lab2_list-2.png tests ------------------- #
    # #2 Threads
    # ./lab2_list --threads=2 >> lab2_list.csv
    # ./lab2_list --iterations=10 --threads=2 >> lab2_list.csv
    # ./lab2_list --iterations=100 --threads=2 >> lab2_list.csv
    # ./lab2_list --iterations=1000 --threads=2 >> lab2_list.csv
    # #4 Threads
    # ./lab2_list --threads=4 >> lab2_list.csv
    # ./lab2_list --iterations=10 --threads=4 >> lab2_list.csv
    # ./lab2_list --iterations=100 --threads=4 >> lab2_list.csv
    # ./lab2_list --iterations=1000 --threads=4 >> lab2_list.csv
    # #8 Threads
    # ./lab2_list --threads=8 >> lab2_list.csv
    # ./lab2_list --iterations=10 --threads=8 >> lab2_list.csv
    # ./lab2_list --iterations=100 --threads=8 >> lab2_list.csv
    # ./lab2_list --iterations=1000 --threads=8 >> lab2_list.csv
    # #12 Threads
    # ./lab2_list --threads=12 >> lab2_list.csv
    # ./lab2_list --iterations=10 --threads=12 >> lab2_list.csv
    # ./lab2_list --iterations=100 --threads=12 >> lab2_list.csv
    # ./lab2_list --iterations=1000 --threads=12 >> lab2_list.csv
    # #2 Threads + yield=i
    # ./lab2_list --yield=i --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=2 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=4 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=8 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=16 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=32 --threads=2 >> lab2_list.csv
    # #4 Threads + yield=i
    # ./lab2_list --yield=i --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=2 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=4 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=8 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=16 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=32 --threads=4 >> lab2_list.csv
    # #8 Threads + yield=i
    # ./lab2_list --yield=i --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=2 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=4 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=8 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=16 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=32 --threads=8 >> lab2_list.csv
    # #12 Threads + yield=i
    # ./lab2_list --yield=i --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=2 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=4 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=8 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=16 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=i --iterations=32 --threads=12 >> lab2_list.csv
    # #2 Threads + yield=d
    # ./lab2_list --yield=d --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=2 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=4 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=8 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=16 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=32 --threads=2 >> lab2_list.csv
    # #4 Threads + yield=d
    # ./lab2_list --yield=d --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=2 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=4 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=8 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=16 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=32 --threads=4 >> lab2_list.csv
    # #8 Threads + yield=d
    # ./lab2_list --yield=d --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=2 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=4 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=8 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=16 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=32 --threads=8 >> lab2_list.csv
    # #12 Threads + yield=d
    # ./lab2_list --yield=d --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=2 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=4 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=8 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=16 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=d --iterations=32 --threads=12 >> lab2_list.csv
    # #2 Threads + yield=il
    # ./lab2_list --yield=il --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=2 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=4 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=8 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=16 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=32 --threads=2 >> lab2_list.csv
    # #4 Threads + yield=il
    # ./lab2_list --yield=il --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=2 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=4 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=8 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=16 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=32 --threads=4 >> lab2_list.csv
    # #8 Threads + yield=il
    # ./lab2_list --yield=il --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=2 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=4 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=8 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=16 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=32 --threads=8 >> lab2_list.csv
    # #12 Threads + yield=il
    # ./lab2_list --yield=il --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=2 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=4 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=8 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=16 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=il --iterations=32 --threads=12 >> lab2_list.csv
    # #2 Threads + yield=dl
    # ./lab2_list --yield=dl --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=2 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=4 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=8 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=16 --threads=2 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=32 --threads=2 >> lab2_list.csv
    # #4 Threads + yield=dl
    # ./lab2_list --yield=dl --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=2 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=4 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=8 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=16 --threads=4 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=32 --threads=4 >> lab2_list.csv
    # #8 Threads + yield=dl
    # ./lab2_list --yield=dl --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=2 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=4 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=8 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=16 --threads=8 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=32 --threads=8 >> lab2_list.csv
    # #12 Threads + yield=dl
    # ./lab2_list --yield=dl --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=2 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=4 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=8 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=16 --threads=12 >> lab2_list.csv
    # ./lab2_list --yield=dl --iterations=32 --threads=12 >> lab2_list.csv
    # # ------------- end of lab2_list-2.png tests ------------------- #

    # # ------------- start of lab2_list-3.png tests ------------------- #
    # #sync=s, all variations of yield
    # ./lab2_list --threads=12 --iterations=32 --yield=i  --sync=s >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=d  --sync=s >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=l  --sync=s >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=il --sync=s >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=id --sync=s >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=dl --sync=s >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=idl --sync=s >> lab2_list.csv
    # #sync=m, all variations of yield
    # ./lab2_list --threads=12 --iterations=32 --yield=i  --sync=m >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=d  --sync=m >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=l  --sync=m >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=il --sync=m >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=id --sync=m >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=dl --sync=m >> lab2_list.csv
    # ./lab2_list --threads=12 --iterations=32 --yield=idl --sync=m >> lab2_list.csv
    # # ------------- end of lab2_list-3.png tests ------------------- #