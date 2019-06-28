#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc,char *argv[]){
	if(argc != 3){
		printf("ErrorNum 10003: Argument Error,Pls check Argument!\n");
		return -1;
	}
	//int truncate(const char *path, off_t length);
	//int ftruncate(int fd, off_t length);
	int length;
	sscanf(argv[2],"%d",&length);
	truncate(argv[1],length);
	return 0;
}

