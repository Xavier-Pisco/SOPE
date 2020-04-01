#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/stat.h>

int main(){

    int fd, n, time = 30;
    char name[256];
    mkfifo("/tmp/fifo_chg", 0660);
    fd = open("/tmp/fifo_chg", O_RDONLY);

    for (int i = 0; i < time; i++){
        sleep(1);
        n = read(fd, name, 256);
        if (n > 0){
            write(STDOUT_FILENO, "CHEGOU ", 7);
            write(STDOUT_FILENO, name, n);
            write(STDOUT_FILENO, "\n", 1);
        }
    }
    close(fd);
    exit(0);
}