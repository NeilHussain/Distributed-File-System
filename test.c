#include <stdio.h>

main(){

	FILE* fd = fopen("file.txt", "w");
	printf("%d\n", fd);
	FILE* fd1 = fopen("file1.txt", "w");
	printf("%d-----%d\n", fd1, fd);
}
