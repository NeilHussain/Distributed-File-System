#include <stdio.h>

main(){
	
	char buffer[1024];
	strcat(buffer, "asdfg");
	printf("%d\n", (int)sizeof(buffer));
}
