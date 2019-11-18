all: client server

CC = gcc

CC += $(D)
CFLAGS = -c -Wall

client:client.o
	$(CC) -o client client.o

server:server.o
	$(CC) -o server server.o

client.o:client.c
	$(CC) -g -c client.c

server.o:server.c
	$(CC) -g -c server.c

clean:
	rm -rf *.o client server
