#include <stdio.h>
#include <stdlib.h>
#include "clientSNFS.h"

//Sets the server of the client with the params
void setServer(char* IP, int port){

printf("cool go to openSocket\n");
printf("IP: %s, Port: %d\n",IP, port);


}

//Tries to open the file (can fail)
//returns file descriptor if successful, -1 if failure
int openFile(char *name){

return -1;
}

//Attempts to read entire file
//Returns number of byte reaad, -1 otherwise
int readFile(int fd, void *buf){



return -1;
}

//Writes the the entire buffer
//Returns number of bytes written, -1 otherwise
int writeFile(int fd, void *buf){



return -1;
}

//Returns info about the file
int statFile(int fd, struct fileStat *buf){



return 0;
}

//Closes the given file, should fail on illegal operations
int closeFile(int fd){



return 0;
}




