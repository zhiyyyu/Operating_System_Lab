#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define BUFSIZE (1024)

int main(int argc,char* argv[])
{ 
    if(argc < 3){
        printf("Usage: cp [path1] [path2]\n");
        return 1;
    }
    printf("src: %s, dst: %s\n", argv[1], argv[2]);
    long ret = syscall(600, argv[1], argv[2]);
    printf("return code is: %ld\n", ret);
    
    return 0;
}