#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];
    pid_t pid;
    int n = 3, i = 0;
    pipe(fd);

    for (i = 0; i < n; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            break;
        }
    }

    //兄弟进程
    if (i == 0)
    {
        printf("Brother1 pid = %d, ppid = %d\n", getpid(), getppid());
        //1. 关闭写端
        close(fd[1]);
        //2. 先重定向
        dup2(fd[0], STDIN_FILENO);//标准输入重定向到管道写读端
        //3. 执行execlp
        char buf[256] = {0};
        while(1)
        {
            memset(buf, 0, sizeof(buf));
            int ret =  read(fd[0], buf, sizeof(buf));
            if (ret == 0)
            {
                printf("read over");
                break;
            }
        }
    }

    //兄弟进程
    else if (i == 1)
    {
        printf("Brother2 pid = %d, ppid = %d\n", getpid(), getppid());
        //1. 关闭读端
        close(fd[1]);
        //2. 先重定向，标准输出重定向到管道读端
        dup2(fd[0], STDIN_FILENO);
        char buf[256] = {0};
        while(1)
        {
            memset(buf, 0, sizeof(buf));
            int ret =  read(fd[0], buf, sizeof(buf));
            if (ret == 0)
            {
                printf("read over");
                break;
            }
        }
    }
    //兄弟进程
    else if (i == 2)
    {
        printf("Brother3 pid = %d, ppid = %d\n", getpid(), getppid());
        //1. 关闭读端
        close(fd[0]);
        //2. 先重定向，标准输出重定向到管道读端
        dup2(fd[1], STDOUT_FILENO);
        //3. 写数据到写端
        int num = 0;
        char buf[256] = {0};
        while(1)
        {
            memset(buf, 0, sizeof(buf));
            sprintf(buf, "from broth3 %d\n", num++);
            int ret = write(fd[1], buf, sizeof(buf));
            if (ret == -1)
            {
                perror("write err:");
                break;
            }
            sleep(1);
        }
    }
   else if (i == 3)
    {
        //parent
        //父亲需要关闭读写两端
        close(fd[0]);
        close(fd[1]);
        //回收子进程
        wait(NULL);
        wait(NULL);
        wait(NULL);
    }

    return 0;
}
