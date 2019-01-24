make default

echo "This is test 1" > input.txt
echo | ./simpsh --rdonly input.txt &> /dev/null
if [[ $? -eq 0 ]]; then 
	echo "Test1 Passed: rdonly works correctly"
else 
	echo "Test1 Failed: rdonly does not work; returns $?"
fi 

echo "This is test 2" > output.txt
echo | ./simpsh --wronly output.txt &> /dev/null
if [[ $? -eq 0 ]]; then 
	echo "Test2 Passed: wronly works correctly"
else 
	echo "Test2 Failed: wronly does not work; returns $?"
fi 

touch err.txt 
echo | ./simpsh --rdonly input.txt --wronly output.txt --wronly err.txt --command 0 1 2 cat
if [[ $? -eq 0 ]]; then 
	echo "Test3A Passed: command works successfully"
else 
	echo "Test3A Failed: command does not work; returns $?"
fi 
cmp input.txt output.txt &> /dev/null
if [[ $? -eq 0 ]]; then 
	echo "Test3B Passed: input and output redirection works as input.txt matches output.txt"
else 
	echo "Test3B Failed: input and output redirection fails as input.txt and output.txt are not equal; returns $?"
fi 
rm -f input.txt output.txt err.txt

make clean