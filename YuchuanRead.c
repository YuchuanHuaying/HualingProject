#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc,char *argv){
    //int fd = open("/dev/tty",O_RDWR | O_NONBLOCK);
    int fd = open("/dev/tty",O_RDWR);

    int flag=fcntl(fd,F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(fd,F_SETFL,flag);	

    char buf[256]={0};
    int ret = 0;
    while(1){
	ret = read(fd,buf,sizeof(buf));
	if(ret < 0){
	    perror("Read Error:");
	    printf("return values: %d\n",ret);
	}
	if(ret>0){
	    printf("buf is %s\n",buf);
	}
	printf("hehe hello!\n");
	sleep(1);
    }
    close(fd);
    return 0;	
}

