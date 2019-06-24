#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	if(argc != 2){
		printf("ErrorNum 10002: argument error, Pls check argument!\n");
		return -1;
	}
	struct stat mystat;
	stat(argv[1],&mystat);
	return 0;
}

