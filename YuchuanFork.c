#include<stdio.h>
#include<unistd.h>

int main(int argc,char *argv[]){	
	/*
	   printf("Fork() Before Calling\n");
	   int pid = fork();
	   if(pid != 0){
	   printf("This is Parent Process Pid = %d\n",getppid());
	   }else{
	   printf("This is Child Process Pid = %d\n",getpid());
	   }
	   printf("Fork() After Calling\n");

	   int i;
	   for(i=0;i<10;i++){
	   pid_t pid = fork();
	//printf("This is %d Fork() Calling,This is Parent Process Pid = %d\n",i,getppid());
	//printf("This is %d Fork() Calling,This is Child Process Pid = %d\n",i,getpid());
	if(pid == 0){
	sleep(i);
	printf("我是第 %d 个子进程,进程ID = %u\n",(i+1),getpid());
	break;
	}else{
	sleep(i);
	printf("我是第 %d 个父进程，进程ID = %u\n",i+1,getppid());
	}

	//sleep(i);
	//printf("我是第 %d 个子进程,进程ID = %d\n",(i+1),getpid());
	}
	*/
	if(argc < 2)
	{
		printf("./a.out 5\n");
		return -1;
	}

	int i;
	pid_t pid;
	printf("xxxxxxxxxxx\n");
	long int a = strtol(argv[1],NULL,10);  //将字符串转化为10进制整数

	for (i = 0; i < a; i++)
	{
		pid = fork( );  //创建子进程
		if(pid == -1)
		{
			printf("process of %u creat process failurely!\n",getpid( ));  
			perror("fork");
		}  //判断创建进程是否成功，如果当次循环创建不成功，则不结束该进程，进行下一次循环，再次尝试创建（这样等效于少了一次循环）。
		else if(pid == 0)  //如果为子进程，则跳出循环
		{
			break;
		}

		else    //否则（父进程），不执行操作，进入下一次循环
			;
	}

	sleep(i);  //通过i值来区分进程，可见父进程睡眠时间最久，为a秒，最先创建的子进程睡眠时间最少，为0秒。
	//printf("I'am the %dth child process, the ID = %u\n",i+1,getpid( )); //
	//printf("I'am parent process, the ID = %u\n",getpid( ));  //父进程输出
	
	if(i < a)
		printf("I'am the %dth child process, the ID = %u\n",i+1,getpid( )); //子进程输出
	else
		printf("I'am parent process, the ID = %u\n",getpid( ));  //父进程输出
	

	return 0;
}




