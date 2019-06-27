#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    if(argc != 2){
	printf("ErroNum:10001 Argument Error,Pls check Argument!\n");
	return -1;
    }
    if(access(argv[1],R_OK) == 0){
	printf("%s : Read Is OK!\n",argv[1]);
    }
    if(access(argv[1],W_OK) == 0){
	printf("%s : Write Is OK!\n",argv[1]);
    }
    if(access(argv[1],X_OK) == 0){
	printf("%s : Exe Is OK!\n",argv[1]);
    }
    if(access(argv[1],F_OK) == 0){
	printf("%s : File Is Exist!\n",argv[1]);	
    }
    return 0;
}

