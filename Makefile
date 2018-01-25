printf : test.o prtfmt.o
	gcc -o printf test.o prtfmt.o

test.o : test.c
	gcc -c test.c

prtfmt.o : prtfmt.h prtfmt.c
	gcc -c prtfmt.c

