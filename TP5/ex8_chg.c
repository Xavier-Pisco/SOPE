#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Usage: %s username", argv[0]);
        exit(1);
    }

    int fd, usernamelen;

    while((fd = open("/tmp/fifo_chg", O_WRONLY)) == -1){
        sleep(1);
    }

    usernamelen = strlen(argv[1]) + 1;
    write(fd, argv[1], usernamelen);
    close(fd);
    exit(0);
}