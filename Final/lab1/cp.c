#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define BUFSIZE (1024)
 
int copy_file(const char* src, const char* dst){

    char buf[BUFSIZE];
    
    int src_fd = open(src, O_RDONLY, 0666);
    if(src_fd == -1)
    {
        printf("Source file %s doesn't not exist! \n", src);
        return 1;
    }
 
    int dst_fd = open(dst, O_WRONLY | O_CREAT, 0666);
    if(dst_fd == -1)
    {
        printf("Dest file %s can't be created! \n", dst);
        return 1;
    }
 
    int num = -1;
    while((num = read(src_fd, buf, BUFSIZE)) > 0)
    {
        write(dst_fd, buf, num);
    }
    
    close(src_fd);
    close(dst_fd);
    return 0;
}

int main(int argc,char* argv[])
{ 
    if(argc < 3){
        printf("Usage: cp [path1] [path2]\n");
        return 1;
    }
    printf("src: %s, dst: %s\n", argv[1], argv[2]);
    long ret = copy_file(argv[1], argv[2]);
    printf("return code is: %ld\n", ret);
    
    return 0;
}