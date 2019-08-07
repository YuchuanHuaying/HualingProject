#include <stdio.h>
#include <unistd.h>


int main(int argc,char *argv[]){
	int fd[2];
	pid_t pid;

	int ret_pip = pipe(fd);
	if(ret_pip == -1){
		perror("create pipe fialure\n");
		return -1;
	}
	pid = fork();
	if(pid < 0){
		perror("create procces failure\n");
		return -1;
	}else if(pid == 0){
		//子进程逻辑
		//1、关闭写端
		close(fd[1]);
		//将STDIN重定向到管道的读端
		fd[0] = dup2(fd[0],STDIN_FILENO);
		if(fd[0] == -1){
			perror("Redirect failure\n");
			return -1;
		}
		//重定向成功执行grep bash命令
		execlp("grep","grep","bash",NULL);
	}else{
		//父进程逻辑
		//1、父进程要关闭管道的读端
		close(fd[0]);
		//2、父进程要重定向STDOUT到管道的写端
		fd[1] = dup2(fd[1],STDOUT_FILENO);
		if(fd[1] == -1){
			perror("Redirect failure\n");
			return -1;
		}
		//3、执行PS命令
		execlp("ps","ps","-ajx",NULL);
	}	
	return 0;	
}




