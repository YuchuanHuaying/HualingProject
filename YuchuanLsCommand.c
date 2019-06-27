#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>

int main(int argc,char *argv[]){
    if(argc != 2){
	printf("ErroNum : 1000 ,%s Argument Error,Pls check Arguments!\n",argv[1]);
	return -1;
    }
    struct stat sb;
    stat(argv[1],&sb);
    //-rw-rw-r--. 1 dyctester dyctester   824 Jun 23 23:39 YuchuanEcho.c
    //解析属性信息，st_mode,uid,gid,time
    char stmode[10]={0};
    memset(stmode,'-',sizeof(stmode));
    if(S_ISREG(sb.st_mode))
	stmode[0]='-';//普通文件
    if(S_ISDIR(sb.st_mode))
	stmode[0]='d';
    if(S_ISCHR(sb.st_mode))
	stmode[0]='c';
    if(S_ISBLK(sb.st_mode))
	stmode[0]='b';
    if(S_ISFIFO(sb.st_mode))
	stmode[0]='p';
    if(S_ISLNK(sb.st_mode))
	stmode[0]='l';
    if(S_ISSOCK(sb.st_mode))
	stmode[0]='s';
    //解析用户权限
    if(sb.st_mode & S_IRUSR)
	stmode[1]='r';
    if(sb.st_mode & S_IWUSR)
	stmode[2]='w';
    if(sb.st_mode & S_IXUSR)
	stmode[3]='x';
    //解析Group权限
    if(sb.st_mode & S_IRGRP)
	stmode[4]='r';
    if(sb.st_mode & S_IWGRP)
	stmode[5]='w';
    if(sb.st_mode & S_IXGRP)
	stmode[6]='x';
    //解析Others权限
    if(sb.st_mode & S_IROTH)
	stmode[7]='r';
    if(sb.st_mode & S_IWOTH)
	stmode[8]='w';
    if(sb.st_mode & S_IXOTH)
	stmode[9]='x';
    //获取用户id的用户getpwuid()，组id对应的组名getgrgid()
    //struct passwd *passwd_file=getpwuid(&sb.st_uid);
    //struct group *group_file=getgrgid(&sb.st_gid);
    //分析时间
    struct tm *file_tm=localtime(&sb.st_atim.tv_sec);
    //-rw-rw-r--. 1 dyctester dyctester   436 Jun 23 21:01 YuchuanOpenMaxFile.c
    char timebuf[20]={0};
    sprintf(timebuf,"%d月 %d %02d:%02d",file_tm->tm_mon+1,file_tm->tm_mday,file_tm->tm_hour,file_tm->tm_min);
    printf("%s. %ld %s %s %ld %s %s\n",stmode,sb.st_nlink,getpwuid(sb.st_uid)->pw_name,getgrgid(sb.st_gid)->gr_name,sb.st_size,timebuf,argv[1]);
    return 0;
}

