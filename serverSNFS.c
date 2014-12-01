#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>

char* baseFilepath;
int fdNumber = 100;

struct permission{

//int threadID;
FILE filePTR;
int read;
int write;

struct permission* nextPerm;

};
typedef struct permission* permPtr;

void error(char *msg){

    perror(msg);
    exit(1);
}

int getNextFD(){

srand(time(NULL));
return (fdNumber += rand());

}

int readFile(){


return 1;
}
int closeFile(int fd){

return (close(fd));




}
int openFile(char* name){


printf("OpenFile in server: %s\n", name);
int fd = open(name, O_RDWR | O_CREAT, 0644);


//give this file some value and send it back, store it in the LL

return fd;

}

char* parseFilename(char* filename, char* buffer, int length){

  //int length = strlen(buffer);
  //char* filename = malloc(sizeof(char)* (length-1));
  strncpy(filename, buffer+1, length);

return filename;
}


void* Server_Thread(void* socket_ptr){

int* socket = (int*) socket_ptr;
int socketNum = *socket;

	char buffer[1024];
	bzero(buffer, 1024);

	/*int n = read(socketNum ,buffer, 255);
	
	if(n < 0){
		error("Sending error");
		exit(1);
	}*/

	//printf("Buffer: %s\n", buffer);

	while(1){
		//printf("Running: %d\n\n", socketNum);
	
		int n = read(*socket ,buffer, 1023);
		//buffer[0] = 
		   //r = read, o = open, w = write, c = close s = statFile		
	
		printf("Buffer in server: %s\n", buffer);
		if(n < 0){
			error("Sending error");
			exit(1);
		}

		switch (buffer[0]){
			case 'h':
				printf("Buffer: %s, Length: %d\n",buffer, (int)strlen(buffer));
							
				bzero(buffer, 256);
			break;
			case 'r':
				readFile();
				bzero(buffer, 256);
				break;
			case 'o':
				//char filename; 
				//const char filename = malloc(sizeof(char)* (strlen(buffer) -1));
				{
					
				   //char* filename = parseFilename(buffer);

				   int length = strlen(buffer);
  				   char* filename = malloc(sizeof(char)* (length-1 + strlen(baseFilepath)));
				   parseFilename(filename, buffer, length);
				   printf("Filename: %s\n", filename);
					
					char* temp = malloc(strlen(baseFilepath) + strlen(filename));
					strcpy(temp, baseFilepath);
	
				   strcat(temp, filename);
					filename = temp;

				   printf("File path: %s\n", filename);
				   int fd = openFile(filename);				
				   bzero(buffer, 256);
				   sprintf(buffer, "%d", fd);
				   
					printf("Writing Buffer: %s\n", buffer);
					int n = write(socketNum ,buffer, 255);
					if(n < 0){
					//error
					}

					bzero(buffer, 256);
				  //free(filename);
					
				}
				break;
			case 'w':
				break;
			case 'c':
				{
				   int fd = atoi(buffer+1);
				   printf("Fd is c block: %d", fd);
					
			
			     	   bzero(buffer, 256);
				   sprintf(buffer, "%d", closeFile(fd));
				   
					
				   printf("Writing Buffer: %s\n", buffer);
			  	   int n = write(socketNum ,buffer, 255);
					if(n < 0){
					   //error
					}

					bzero(buffer, 256);

				puts("Got to close file");
				
				}
					break;
			case 's':
				printf("Howdy from %d\n\n", socketNum);
					

				bzero(buffer, 256);				
				break;
			default:
				//printf("Got some message: %c on socket: %d\n", buffer[0], socketNum);
				bzero(buffer, 256);
				//puts("Hit default");				
				usleep(100);
			
				break;
		}
		
	}

	close(*socket);

return NULL;
}

void acceptConnections(int port){

	socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
 
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(port);
     
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
    	 
	
     	listen(sockfd,5);
	clilen = sizeof(cli_addr);

while (1) {

	//printf("~While loop~\n");        

	 int newsockfd = accept(sockfd, 
               (struct sockaddr *) &cli_addr, &clilen);
	printf("newsockfd: %d\n", newsockfd);
         
	if (newsockfd < 0) 
             error("ERROR on accept");
        
	pthread_t *server = malloc(sizeof(pthread_t));
	int ret = pthread_create(server, NULL, Server_Thread, &newsockfd);

	if(ret != 0)
		error("Error making new thread");

}
	/*bzero(buffer, 256);

	n = write(sockfd,buffer, strlen(buffer));
	if(n < 0){
		error("Sending error");
		exit(1);
	}*/

/* end of while */

}

int main(int argc, char *argv[]){
	int port;
	char filepath[128];
	bzero(filepath, 128);

	
 
	if(argc != 5){
		printf("Invalid argument number: serverSNFS takes 5 arguments\n" );
		return 0;
	}else{
		if(!strcmp(argv[1], "-port"))
			port = atoi(argv[2]);
		else{
			printf("Wrong argument formatting!\n");
			return 0;
		}
		if(!strcmp(argv[3], "-mount")){
			strcpy(filepath, argv[4]);
			int status;
			status = mkdir(filepath,  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			
			if(status){

					if(errno == EEXIST)
					error("directory already in use");
				else
					error("Some error occurs in directory creation");
				}
			

				if(filepath[strlen(filepath)-1] != '/'){
					filepath[strlen(filepath)] = '/';
					filepath[strlen(filepath)+1] = '\0';
				
					
			
				
				baseFilepath = filepath;
			}
				//printf("basepath: %s\n", baseFilepath);
				//Don't need an error here, just use that path when making/reading files
				
			
		}
		else{
			printf("Wrong argument formatting!\n");
			return 0;
		}
	}

 
	printf("Port: %d, Filepath: %s\n", port, filepath);	
	//DO some error handling

	acceptConnections(port);

	//printf("ServerSNFS\n");

	return 0;
}
