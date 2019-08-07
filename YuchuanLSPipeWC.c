#include <stdio.h>
#include <unistd.h>



int main(int argc,char *argv[]){
	pid_t pid;
	int fd[2];
	int ret_pi = pipe(fd);
	if(ret_pi == -1){
		perror("create pipe failure");
		return -1;
	}
	pid = fork();
	if(pid < 0){
		perror("create proccess failure");
		return -1;
	}else if(pid == 0){
		//子进程逻辑：从管道读端读取数据让wc -l 执行功能，关闭管道写端，正常WC是从STDIN读取数据。
		//关闭管道写端
		close(fd[1]);
		//将STDIN重定向到读端
		dup2(fd[0],STDIN_FILENO);
		//执行WC命令
		execlp("wc","wc","-l",NULL);
	}else{
		//父进程逻辑：使用ls将数据写到管道的写端，关闭管道的读端，我们常用的ls输出到STDOUT
		//关闭管道的读端
		close(fd[0]);
		//将STDOUT重定向到管道的写端
		dup2(fd[1],STDOUT_FILENO);
		//执行ls命令
		execlp("ls","ls",NULL);
	}
	return 0;
}
