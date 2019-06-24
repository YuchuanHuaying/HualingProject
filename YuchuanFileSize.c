#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc,char *argv[]){
    if(argc != 2){
	printf("ErroNum 10001 : YuchuanFileSize.sh argument erro, Pls check arguments!");
	return -1;
    }
    int fd = open(argv[1],O_RDONLY);
    int ret = lseek(fd,0,SEEK_END);
    printf("%s File size is : %d\n",argv[1],ret);
    close(fd);
    return 0;
}
