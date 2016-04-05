CFLAGS=-g $(shell pkg-config --cflags gtk+-3.0 --libs gtk+-3.0)

all: gol

gol_test: main2.o world.c
	gcc $(CFLAGS) main2.o world.o -o gol_test

main2.o: main2.c world.o
	gcc $(CFLAGS) -c main2.c -o main2.o

gol: main.o world.o gui.o
	gcc $(CFLAGS) main.o world.o gui.o -o gol

main.o: main.c world.h gui.h
	gcc $(CFLAGS) -c main.c

world.o: world.c world.h
	gcc $(CFLAGS) -c world.c

gui.o: gui.c gui.h builder.ui
	gcc $(CFLAGS) -c gui.c

clean:
	rm *.o
	rm gol
	rm gol_test
