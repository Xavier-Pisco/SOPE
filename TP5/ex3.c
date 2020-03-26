#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_NAME_SIZE 50

int main(int argc, char* argv[]){
    
    int fd[2];

    if (argc != 2){
        printf("Usage %s file", argv[0]);
        exit(1);
    }

    pipe(fd);

    if (fork() > 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("cat", "cat", argv[1], NULL);
    } else {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("sort", "sort", NULL);
    }

    exit(0);
}