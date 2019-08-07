#include <stdio.h>
#include <unistd.h>

int var=100;

int main(int argc,char *argv[]){
	pid_t pid=fork();
	if(pid == 0){
		//son
		printf("This is Son Process pid = %d , Parent PPid = %d , var = %d;\n",getpid(),getppid(),var);
		var=1000;
		//修改全局变量后
		printf("Modif After This is Son Process pid = %d , Parent PPid = %d , var = %d;\n",getpid(),getppid(),var);
		sleep(3);
	}else if(pid > 0){
		//Parent
		sleep(2);
		printf("This is Parent Process pid = %d , Parent PPid = %d , var = %d;\n",getpid(),getppid(),var);
		var = 2000;
		printf("Modif After This is Parent Process pid = %d , Parent PPid = %d , var = %d;\n",getpid(),getppid(),var);
	}
	return 0;
}





