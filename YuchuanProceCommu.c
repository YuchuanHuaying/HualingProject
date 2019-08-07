#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(int argc,char *argv[]){
	int fd[2];
	pipe(fd);
	pid_t pid = fork();

	if(pid > 0){
		//父进程关闭读端
		close(fd[0]);

		char buf[256] = {0};
		int num = 0;
		while(1){
			memset(buf,0,sizeof(buf));
			sprintf(buf,"data from parent %d\n",num++);
			write(fd[1],buf,sizeof(buf));
			sleep(1);
			if(num > 28){
				break;
			}
		}
	}else if(pid == 0){
		//子进程
		close(fd[1]);

		char buf[256] = {0};
		while(1){
			memset(buf,0,sizeof(buf));
			int ret = read(fd[0],buf,sizeof(buf));	
			if(ret > 0){
				write(STDOUT_FILENO,buf,ret);
			}else if(ret == 0){
				printf("read over!\n");
				break;
			}
		}
	}	
	return 0;
}





