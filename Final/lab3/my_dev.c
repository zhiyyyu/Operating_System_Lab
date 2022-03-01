#include <stdio.h>
#include <sys/fcntl.h>

#define BUF_SIZE 1024

int main(int argc, char* argv[]){
    int fd = open("/dev/test", O_RDWR);
    char buf[BUF_SIZE] = "there is a test for my_dev.";
    if(argc > 1){
        sprintf(buf, argv[1]);
    }
    if(fd == -1){
        printf("Device Not Exsits.\n");
        return 1;
    }
    write(fd, buf, sizeof(buf));
    printf("write to device: %s\n", buf);
    read(fd, buf, sizeof(buf));
    printf("read from device: %s\n", buf);
    close(fd);
    return 0;
}