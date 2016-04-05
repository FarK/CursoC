all: person

person: main.o person.o
	gcc main.o person.o -o person

main.o: main.c person.h
	gcc -c main.c

person.o: person.h person.c
	gcc -c person.c
