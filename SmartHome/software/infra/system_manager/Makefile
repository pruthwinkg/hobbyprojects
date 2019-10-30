CC = gcc
CFLAGS = -g -c -Wall


system_mgr:system_mgr.o main.o
	gcc -o system_mgr system_mgr.o main.o
main.o:system_mgr.h
	gcc -g -c -Wall main.c
system_mgr.o:system_mgr.h
	gcc -g -c -Wall system_mgr.c system_mgr_client_tbl.c
clean:
	rm -rf *.o system_mgr
