CFLAGS=-g

all: s c

s: server.o talk.o
	gcc $(CFLAGS) -o s server.o talk.o

c: client.o talk.o
	gcc $(CFLAGS) -o c client.o talk.o

server.o: server.c
	gcc $(CFLAGS) -c server.c

client.o: client.c
	gcc $(CFLAGS) -c client.c

talk.o: talk.c talk.h
	gcc $(CFLAGS) -c talk.c

clean:
	rm *.o
	rm s c
