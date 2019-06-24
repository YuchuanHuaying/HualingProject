#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    if(argc != 2){
	printf("ErroNum:10000; cat command agrc erro, Pls check argc!\n");
	return -1;
    }
    int fd = open(argv[1],O_RDONLY);
    char buf[256];
    int ret = -1;
    while(ret != 0){
	ret = read(fd,buf,sizeof(buf));
	write(STDOUT_FILENO,buf,ret);	
    }
    close(fd);
    return 0;
}

