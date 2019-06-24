#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc,char *argv[]){
    if(argc < 2){
	printf("ErroNum: 10000 ,YuchuanEcho argc Erro!");
	return -1;
    }
	//这是注释，供阅读代码.
    char buf[2]={0};
    int ret = -1;
    int fd = open(argv[1],O_RDWR | O_CREAT,0666);
    //写完后文件的指针指向了文件结束的位置
    //write(fd,argv[2],sizeof(argv[2]));
    write(fd,argv[2],sizeof(argv[2]));
    //需要移动读写位置
    lseek(fd,0,SEEK_SET);
    //char buf[256]={0};
    /*ret = read(fd,buf,sizeof(buf));
      if(ret != 0){	
      write(STDOUT_FILENO,buf,ret);
      }
      */
    while(ret != 0){
	ret = read(fd,buf,sizeof(buf));
	write(STDOUT_FILENO,buf,ret);
    }
    close(fd);
    return 0;
}


//niubibuzheshi
