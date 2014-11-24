COMPILER = gcc
CCFLAGS = -Wall -std=c99

all:clientapp serverSNFS


clientapp: clientapp.o clientSNFS.o 
	$(COMPILER) $(CCFLAGS) clientapp.o clientSNFS.o -o clientapp

serverSNFS: serverSNFS.o 
	$(COMPILER) $(CCFLAGS) serverSNFS.o -lpthread -o serverSNFS

serverSNFS.o: serverSNFS.c
	$(COMPILER) $(CCFLAGS) -c serverSNFS.c

clientSNFS.o: clientSNFS.c clientSNFS.h
	$(COMPILER) $(CCFLAGS) -c clientSNFS.c clientSNFS.h

clientapp.o: clientapp.c clientSNFS.h
	$(COMPILER) $(CCFLAGS) -c clientapp.c clientSNFS.h


clean:
	rm -f *.o
	rm -f fileFullPath.txt
	rm -f clientapp serverSNFS
