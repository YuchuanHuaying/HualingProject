#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int count=0;
int ReadDirFileCount(char *dirname){
	/*
	if(dirname == NULL){
		printf("Input Dir cannot empty,Pls Input dirname !\n");
		return -1;
	}
	*/
	//1打开目录
	DIR *dirp=opendir(dirname);
	if(dirp == NULL){
		printf("Input DirName Error,Pls again Input!\n");
		return -1;
	}
	//2读目录
	struct dirent *direntp=NULL;
	while((direntp=readdir(dirp))!=NULL){//如果不等于NULL代表读到目录的结尾了
		//printf("%s : %d\n",direntp->d_name,direntp->d_type);
		if(direntp->d_type == DT_DIR){
			if(strcmp(".",direntp->d_name)==0 || strcmp("..",direntp->d_name)==0){
				continue;
			}
			//注意进程的工作路径不能直接打开子目录，
			//使用dirname拼接子目录
			char new_dir_name[256]={0};
			sprintf(new_dir_name,"%s%s",dirname,direntp->d_name);
			ReadDirFileCount(new_dir_name);
			printf("%s : %d\n",new_dir_name,direntp->d_type);
		}
		if(direntp->d_type == DT_REG){
			count++;
			printf("%s : %d\n",direntp->d_name,direntp->d_type);
		}
	}
	//3关闭目录
	closedir(dirp);
	printf("count = %d\n",count);
}

int main(int argc,char *argv[]){
	if(argc != 2){
		printf("ErrorNum :10001 ,Argument Error,Pls check Argument! \n");
		return -1;
	}
	ReadDirFileCount(argv[1]);
	return 0;
}




