make

LC_ALL=en_US.UTF-8

echo " "

echo "===========Test 1============="
sort -r <pg98.txt >output1.txt 2>error.txt
tr [:lower:] [:upper:] <pg98.txt >output2.txt 2>error.txt
echo "=================="
times
echo "=================="
echo "===========Test 1============="
rm output1.txt output2.txt error.txt

echo " "

echo "===========Test 2============="
(sort -r < pg98.txt | cat pg98.txt - | tr A-Z a-z >output.txt) 2>>error.txt
echo "=================="
times
echo "=================="
echo "===========Test 2============="
rm output.txt error.txt

echo " "

echo "===========Test 3============="
(time -p sleep 2 > test3.txt | cat pg98.txt - | tr A-Z a-z | sort -r > output.txt) 2>>error.txt
echo "=================="
times
echo "=================="
echo "===========Test 3============="
rm test3.txt output.txt error.txt

echo " " 

make clean