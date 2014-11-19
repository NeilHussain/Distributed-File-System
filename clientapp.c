#include <stdio.h>
#include <stdlib.h>
#include "clientSNFS.h"

void OpenSocket(char* ip, int port){

setServer(ip, port);


}

void OpenFile(char* filename){



}

int main(int argc, char *argv[]){

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
	

	OpenFile(filename);
	OpenSocket(IP,port);

	

	//printf("Clientapp\n");
	return 0;
}
