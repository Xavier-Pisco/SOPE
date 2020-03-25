#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_NAME_SIZE 50

int main(int argc, char* argv[]){
    
    int fd[2], f, temp;

    if (argc != 2){
        printf("Usage %s file", argv[0]);
        exit(1);
    }

    pipe(fd);

    if ((f = open(argv[1], O_RDONLY, NULL)) == -1){
        perror(argv[1]);
        exit(2);
    }

    temp = dup(STDOUT_FILENO);
    dup2(STDIN_FILENO, fd[1]);

    if (fork() > 0) {
        execlp("cat", "cat", argv[1], NULL);
    } else {
        execlp("sort", "sort", fd[0], NULL);
    }

    dup2(temp, STDOUT_FILENO);
    exit(0);
}