#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){

	char* name = argv[1];
	while(1){
	struct stat st;
	if(stat(name, &st) == 0)
		printf("file size %Zu\n", st.st_size);
	gets(name);
}
	return 0;	
}
