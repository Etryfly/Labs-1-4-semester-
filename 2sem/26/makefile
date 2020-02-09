build: main.o udt.o sort.o
	gcc -o main main.o sort.o udt.o

sort.o: sort.c
	gcc -c sort.c

main.o: main.c
	gcc -c main.c

udt.o: udt.c
	gcc -c udt.c

clean :
	rm -f *.o main


