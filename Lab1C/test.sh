make

echo "===========Test 1============="
./simpsh --creat --excl --rdwr test1io.txt --wait \
  --catch 31 --command 0 0 0 ./grading_helper 11 a b c d \
  --verbose --command 0 0 0 ./grading_helper 31 e f g h \
  --command 0 0 0 ./grading_helper 9 i j k l --wait \
  --command 0 0 0 bash -c "exit 50" --default >c25out.txt 2>c25err.txt
if [[ $? -eq 0 ]]; then 
	echo "Test1 Passed: rdonly works correctly."
else 
	echo "Test1 Failed: rdonly does not work."
fi
echo "===========Test 1============="

times

make clean