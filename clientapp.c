#include <stdio.h>
#include <stdlib.h>
#include "clientSNFS.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <strings.h>

char * getline(void) {
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

void OpenSocket(char* ip, int port){

	setServer(ip, port);
}

void  OpenFile(char* filename){

	//int fd = 100;
	int fd = openFile(filename);
	printf("File: %s FD: %d\n", filename, fd);
}
void ReadFile(int fd){

	//need to get file descripter from filename or something like that
	printf("File: %d\n", fd);
	char buff[1024];
	bzero(buff, 1024);	

	int ret = readFile(fd ,buff);
	if(ret >= 0){
		printf("%s", buff);
	}else{
		printf("Readfile failure return value: %d", ret);

	}

}
void WriteFile(char* filename){

	//need to get file descripter from filename or something like that
	printf("File: %s\n", filename);

}
void CloseFile(int fd){

	int ret = closeFile(fd);
	printf("Closing file: %d Return Value: %d\n", fd, ret);
	

}

void StatFile(char* filename){
	struct fileStat* buf =NULL;
	statFile(6, buf);
}
void getCommands(){

int running = 1;
	while(running){

		printf("\nWhat would you like to do? Type:\n   'open' to open a file\n   'read' to read a file\n   'write' to write to a file\n   'stat' to check file stat\n   'close' to close a file\n   'exit' to exit the program\n");
		char* input = "";
		input = getline();
		
		//printf("%s", input);
		char* file = "";
		char* fd = "";
			
		if(strcmp(input, "open\n") == 0){
			printf("\nWhat file would you like to open?\n");
			file = getline();

			//strip the new line char
			file[strlen(file)-1] = 0;
			OpenFile(file);
		
		}else if(strcmp(input, "read\n") == 0){
			
			printf("\nWhat file would you like to read? (File Descriptor)\n");
			fd = getline();
			fd[strlen(fd)-1] =0;
			int fdNum = atoi(fd);
			ReadFile(fdNum);

		}else if(strcmp(input, "write\n") == 0){
			
		}else if(strcmp(input, "close\n") == 0){
			
			printf("\nWhat file would you like to close? (File Descriptor)\n");
			fd = getline();
			
			fd[strlen(fd)-1] = 0;
			int fdNum = atoi(fd);
			CloseFile(fdNum);
		
		}else if(strcmp(input, "exit\n") ==0){

			puts("Exiting...");
			exit(1);
		}else if(strcmp(input, "stat\n") ==0){
			printf("\nWhat file would you like to check for its stat?\n");
			file = getline();
			file[strlen(file)-1] =0;
						
			StatFile(file);
		}


	}

}

int main(int argc, char *argv[]){


	//ARGS: IP PORT FILENAME
	char* IP = "";
	int port = 0;
	char* filename;

	if(argc != 4){
		return 0;
	}else{
		IP = argv[1];
		port = atoi(argv[2]);
		filename = argv[3];
	}
	

	//OpenFile(filename);
	OpenSocket(IP,port);
	
	getCommands();


	//printf("Clientapp\n");
	return 0;
}
