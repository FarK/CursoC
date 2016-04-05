CFLAGS=-ggdb

all: gol

gol: main.o world.o
	gcc $(CFLAGS) main.o world.o -o gol

main.o: main.c world.h
	gcc $(CFLAGS) -c main.c

world.o: world.c world.h
	gcc $(CFLAGS) -c world.c

clean:
	rm *.o
	rm gol
