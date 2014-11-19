#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
int port;
char* filepath;


if(argc != 3){
printf("Invalid argument number: serverSNFS takes 2 arguments\n		TCP Port Number, filepath" );

}else{
port = atoi(argv[1]);
filepath = argv[2];
}

printf("Port: %d, Filepath: %s", port, filepath);


printf("ServerSNFS\n");

return 0;
}
