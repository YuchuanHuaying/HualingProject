#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    if(argc != 2){
	printf("ErroNum 10003 : arguments erro, Pls check argument\n");
	return 0;
    }
    int fd = open(argv[1],O_RDWR | O_CREAT,0666);
    lseek(fd,1024,SEEK_END);
    write(fd,"a",1);
    close(fd);
    return 0;
}
