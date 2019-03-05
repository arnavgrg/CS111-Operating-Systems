#NAME: Arnav Garg
#UID: 304911796
#EMAIL: arnavgrg@ucla.edu

.SILENT:

default:
	make clean
	touch lab3b
	chmod +x lab3b
	echo "#!/bin/bash"  > lab3b
	echo "python lab3b.py "$$@"' >> lab3b
	echo 'EXIT_CODE=$$?' >> lab3b
	echo 'exit $$EXIT_CODE' >> lab3b
	echo "Success"

dist:
	tar -czf lab3b-304911796.tar.gz Makefile README lab3b.py

clean:
	rm -rf *.tar.gz lab3b