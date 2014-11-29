#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include "clientSNFS.h"

#define h_addr h_addr_list[0] /* for backward compatibility */

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

//Sets the server of the client with the params
void setServer(char* serverIdent, int port){

	printf("cool got to openSocket\n");
	printf("IP: %s, Port: %d\n",serverIdent, port);
	
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
   	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
   	if (sockfd < 0) 
        error("ERROR opening socket");
    
	//##gets the host of the server by the given host name or IP##//
	
	server = gethostbyname(serverIdent);
	
	if(server == NULL){
	server = gethostbyaddr(serverIdent, 4, AF_INET);
	}	 

	if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    	}

	//########################################################/

	// Fills structs
    	bzero((char *) &serv_addr, sizeof(serv_addr));
    	serv_addr.sin_family = AF_INET;
    	
	bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   	serv_addr.sin_port = htons(port);
   	
	//attempts to the connect
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
	
	char* buffer;
	buffer = "Hi!!!!";
	write(sockfd, buffer, strlen(buffer));
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




