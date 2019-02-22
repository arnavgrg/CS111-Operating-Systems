make default

LC_ALL=en_US.UTF-8

echo " "

echo "===========Test 1============="
./simpsh --profile --rdonly pg98.txt --creat --rdwr output1.txt --creat --rdwr output2.txt \
--creat --wronly error.txt --command 0 1 3 sort -r --command 0 2 3 tr [:lower:] \
[:upper:] >test1out.txt 2>test1err.txt;
cat test1out.txt;
rm test1out.txt test1err.txt output1.txt output2.txt error.txt;
echo "===========Test 1============="

echo " "

echo "===========Test 2============="
./simpsh \
  --profile --rdonly pg98.txt \
  --pipe --pipe \
  --creat --trunc --wronly output.txt \
  --creat --append --wronly error.txt \
  --command 0 2 6 sort -r --close 2 \
  --command 1 4 6 cat pg98.txt - --close 4 \
  --command 3 5 6 tr [:upper:] [:lower:] >test2out.txt 2>test2err.txt;
cat test2out.txt;
rm output.txt error.txt test2out.txt test2err.txt;
echo "===========Test 2============="

echo " "

echo "===========Test 3============="
./simpsh \
--profile --creat --rdwr test3.txt \
--rdonly pg98.txt \
--creat --wronly output.txt \
--creat --wronly error.txt --pipe --pipe --pipe \
--command 0 0 0 time -p sleep 2 \
--command 1 5 3 cat --close 5 \
--command 4 7 3 tr [:lower:] [:upper:] --close 7 \
--command 6 2 3 sort -r >test3out.txt 2>test3err.txt;
cat test3out.txt;
rm test3.txt test3out.txt test3err.txt output.txt error.txt;
echo "===========Test 3============="