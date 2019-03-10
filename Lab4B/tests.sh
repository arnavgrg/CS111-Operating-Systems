#!/bin/sh                                                                                                                                                                                                   

echo "Smoke Tests started:"

echo "Echoing START STOP PERIOD=2 OFF while running lab4b..."

{ echo "START"; sleep 3; echo "STOP"; sleep 2; echo "START"; echo "PERIOD=2"; sleep 4; echo "OFF"; } | ./lab4b --log=log.txt

if [ $? -eq 0 ]
then
	echo "PASSED: Program exited correctly with return value 0!"
else
    echo "FAILED: Program incorrectly reports errors"
fi

if [ ! -s log.txt ]
then
    echo "FAILED: Logfile not created"
else
    echo "PASSED: Logfile was created"
fi

counter=0

for input_val in START STOP PERIOD OFF SHUTDOWN
do
    grep "$input_val" log.txt > /dev/null
    if [ $? -eq 0 ]
    then
        counter=$((counter+1))
        echo "Logfile contains $input_val"
    else 
        echo "Logfile is missing $input_val"
    fi
done

if [ "$counter" -ne 5 ]
then
    echo "FAILURE!! Logfile is missing required log entries"
else    
    echo "SUCCESS! Logfile correctly logs all required entries"
fi

rm log.txt