#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
	printf("./a.out files\n");
	return -1;
    }
    int fd=open(argv[1],O_RDONLY | O_CREAT,0666);
    close(fd);
    return 0;
}

