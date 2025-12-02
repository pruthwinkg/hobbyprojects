all:client server

client:client.o
	gcc -o client client.o
server:server.o
	gcc -o server server.o
client.o:
	gcc -c -g client.c -Wall
server.o:
	gcc -c -g server.c -Wall
clean:
	rm -rf *.o server client
