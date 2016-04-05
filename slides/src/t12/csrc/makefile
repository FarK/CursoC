CFLAGS = -Wall -Wextra

all: vehicles

vehicles : vehicle.o main.o
	gcc main.o vehicle.o car.c -o vehicles

main.o : main.c vehicle.h
	gcc $(CFLAGS) -c main.c

vehicle.o : vehicle.c vehicle.h
	gcc $(CFLAGS) -c vehicle.c

car.o : car.c car.h
	gcc $(CFLAGS) -c car.c

clean:
	rm -f *.o
	rm -f vehicles
