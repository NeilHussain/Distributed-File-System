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
#include <sys/stat.h>
#include <errno.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void* Server_Thread(void* args){

printf("Connection accepted");

return NULL;
}

void acceptConnections(int port){

	printf("Connections Acceptor\n");
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

	 int newsockfd = accept(sockfd, 
               (struct sockaddr *) &cli_addr, &clilen);
         
	if (newsockfd < 0) 
             error("ERROR on accept");
	printf("connection successful\n");
	/*
	pthread_t *server = malloc(sizeof(pthread_t));
	int ret = pthread_create(server, NULL, Server_Thread, NULL);
	
	if(ret == 0){

	printf("Created new thread %u\n", pthread_self());
	}
	*/

	///Create individual processes
	 /*pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             dostuff(newsockfd);
             exit(0);
         }

        else close(newsockfd);*/

     } 



/* end of while */





}

int main(int argc, char *argv[]){
	int port;
	char* filepath;


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
			filepath = argv[4];
			int status;
			status = mkdir(filepath,  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			if(status){
				if(errno == EEXIST)
					error("directory already in use");
				else
					error("Some error occurs in directory creation");
			}
			
		}
		else{
			printf("Wrong argument formatting!\n");
			return 0;
		}

	}

	printf("Port: %d, Filepath: %s\n", port, filepath);	
	//DO some error handling

	acceptConnections(port);

	printf("ServerSNFS\n");

	return 0;
}
