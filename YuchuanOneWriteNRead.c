#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[]){
	int fd[2];
	pid_t pid;
	int n=3,i=0;
	
	int ret_pip = pipe(fd);
	if(ret_pip == -1){
		perror("Create Pipe Failure!\n");
		return -1;
	}
	//创建n个子进程
	for(i=0;i<n;i++){
		pid = fork();
		if(pid < 0){
			perror("Create Child Proccess Failure!\n");
			return -1;
		}else if(pid == 0){
			break;
		}
		sleep(1);
	}
	if(i == 0){
		//第一个子进程
		printf("First Child Proccess Read Data: Pid = %d, PPid = %d\n",getpid(),getppid());
		//子进程1作为读数据，关闭写端。
		close(fd[1]);
		//重定向STDIN 到管道的读端
		dup2(fd[0],STDIN_FILENO);
		//读取数据
		char buf[256] = {0};
		while(1){
			memset(buf,0,sizeof(buf));
			int ret = read(fd[0],buf,sizeof(buf));
			if(ret == 0){
				printf("Read Over!\n");
				break;
			}
		}
	}
	
	if(i == 1){
		//第一个子进程
		printf("Secand Child Proccess Read Data: Pid = %d, PPid = %d\n",getpid(),getppid());
		//子进程1作为读数据，关闭写端。
		close(fd[1]);
		//重定向STDIN 到管道的读端
		dup2(fd[0],STDIN_FILENO);
		//读取数据
		char buf[256] = {0};
		while(1){
			memset(buf,0,sizeof(buf));
			int ret = read(fd[0],buf,size(buf));
			if(ret == 0){
				printf("Read Over!\n");
				break;
			}
		}
	}

	if(i == 2){
		//第三个子进程写数据
		printf("Three Child Proccess Write Data: Pid = %d, PPid = %d\n",getpid(),getppid());
		//写数据关闭读端
		close(fd[0]);
		//重定向标准输出到管道的写端
		dup2(fd[1],STDOUT_FILENO);
		//写数据
		int num = 0;
		char buf[256] = {0};
		while(1){
			memset(buf,0,sizeof(buf));
			sprintf(buf,"From Child Proccess Three Write %d\n",num++);
			int ret = write(fd[1],buf,sizeof(buf));
			if(ret == -1){
				perror("write err:");
				break;
			}
			sleep(1);
		}
	}
	if(i==3){
		//Parent 进程
		//关闭管道的文件描述符
		close(fd[0]);
		close(fd[1]);
		//回收子进程
		wait(NULL);
		wait(NULL);
		wait(NULL);
	}
	return 0;
}




