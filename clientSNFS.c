#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <strings.h>
#include <time.h>
#include <sys/stat.h>
#include "clientSNFS.h"
#define h_addr h_addr_list[0] /* for backward compatibility */

int sockfd;

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
	
   	sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

	//char *buffer;
	//bzero(buffer, 256);

	/*buffer = "ohelloworld.txt";
	//strcpy(buffer, "hello world!");

	printf("Buffer Client: %s", buffer);
	int n = write(sockfd,buffer,strlen(buffer));
	if(n < 0){
		error("Sending error");
		exit(1);
	}*/

	

}

//Tries to open the file (can fail)
//returns file descriptor if successful, -1 if failure
int openFile(char *name){
	
	char buffer[256];
	bzero(buffer, 256);
	//strcpy(buffer, "o");
	buffer[0] = 'o';
	strcat(buffer, name);
	
	//printf("ClientSNFS: %s", buffer);
	printf("Socket FD in clientSNFS: %d\n",sockfd);
	int n = write(sockfd,buffer,(strlen(buffer)));
		
	if(n < 0){
		error("Sending error in openFile");
		exit(1);
	}

	usleep(1000);
	n = read(sockfd, buffer, 255);
	
	if(n < 0){
		error("Reading error openFile");
		exit(1);
	}
	
	int fd = atoi(buffer);
	
	

return fd;
}

//Attempts to read entire file
//Returns number of byte read, -1 otherwise
int readFile(int fd, void *buf){

	char buffer[1024] = "";
	buffer[0] = 'r';
	
	char str[] = "";
	sprintf(str, "%d", fd);
	strcat(buffer, str);

	//printf("%s\n", buffer);	
	
	int n = write(sockfd, buffer, strlen(buffer));
	
	bzero(buffer, 1024);

	n = read(sockfd, buffer, 1024);
	if(n < 0)
		error("Reading error in readFile");
		
	if(strcmp("-1", buffer) == 0)
	    return -1;
	
	printf("what's returned: %s\n", buffer);
    buf = buffer;
    return strlen(buf);
}

//Writes the the entire buffer
//Returns number of bytes written, -1 otherwise
int writeFile(int fd, void *buf){

	char buffer[256];
	bzero(buffer, 256);
	strcat(buffer, "w");
	char str[50] = "";
	sprintf(str, "%d", fd);
	strcat(buffer, str);
	int n = write(sockfd, buffer, strlen(buffer));
	
	if(n < 0)
		error("Sending error in writeFile");
	
	bzero(buffer, 256);
	
	n =  write(sockfd, buf, strlen(buf));
	if(n < 0)
		error("Sending error in writeFile");
	
	usleep(1000);
	n = read(sockfd, buffer, sizeof(buffer));
	if(n < 0)
		error("Receiving error in writeFile");
	
	int ret = atoi(buffer);
	

return ret;
}

//Returns info about the file
int statFile(int fd, struct fileStat *buf){

	char buffer[50] = "";
	strcat(buffer, "s");
	char str[50] = "";
	sprintf(str, "%d", fd);
	strcat(buffer, str);
	int n = write(sockfd, buffer, strlen(buffer));
		
	if(n < 0){
		error("Sending error in statFile");
		exit(1);
	}
	
	n = read(sockfd , buf, sizeof(struct fileStat));
	
    if(n < 0){
		error("Reading fileStat error");
	}
/*	
	printf("filesize is %Zu\n", buf->file_size);
					char atime[30], mtime[30];
					struct tm* timeinfo;
					timeinfo = localtime(&(buf->access_time));
					strftime(atime, 30, "%b %d %H:%M", timeinfo);
					printf("access time: %s\n", atime);
    
					timeinfo = localtime(&(buf->mod_time));
					strftime(mtime, 30, "%b %d %H:%M", timeinfo);
					printf("modi time: %s\n", mtime);
*/
return 0;
}

//Closes the given file, should fail on illegal operations
int closeFile(int fd){

char buffer[256];
char temp[256];
	bzero(buffer, 256);
	//strcpy(buffer, "o");
	buffer[0] = 'c';
	sprintf(temp, "%d", fd);
	strcat(buffer, temp);
	int n = write(sockfd,buffer,(strlen(buffer)));
		
	if(n < 0){
		error("Sending error in closeFile");
		exit(1);
	}

	usleep(1000);
	n = read(sockfd, buffer, 255);
	
	if(n < 0){
		error("Reading error closeFile");
		exit(1);
	}
	
	int ret = atoi(buffer);

return ret;
}




