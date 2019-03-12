#NAME: Arnav Garg
#EMAIL: arnavgrg@ucla.edu
#ID: 304911796

.SILENT:

default:
	gcc -g -Wall -Wextra -lmraa -lm lab4c_tcp.c -o lab4c_tcp
	gcc -g -Wall -Wextra -lmraa -lm -lssl -lcrypto lab4c_tls.c -o lab4c_tls

dist:
	tar -czf lab4c-304911796.tar.gz README Makefile lab4c_tcp.c lab4c_tls.c

clean:
	rm -rf lab4c_tcp lab4c_tls *.tar.gz