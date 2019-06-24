#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    int num=3;
    int fd;
    char file_names[128]={0};
    while(1){
	sprintf(file_names,"temp_%04d",num++);
	fd = open(file_names,O_RDONLY | O_CREAT,0666);
	if(fd < 0){
	    perror("Open File Error:");
	    break;
	}
    }
    close(fd);
    printf("Open File count: %d\n",num);
    return 0;
}

