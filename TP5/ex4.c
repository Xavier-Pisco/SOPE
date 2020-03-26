#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int fd1[2], fd2[2], tmp_stdin, tmp_stdout;

    if (argc != 3){
        printf("Usage: %s directory string", argv[0]);
        exit(1);
    }

    pipe(fd1);
    pipe(fd2);

    tmp_stdin = dup(STDIN_FILENO);
    tmp_stdout = dup(STDOUT_FILENO);

    if (fork() > 0){
        if (fork() > 0){
            dup2(fd1[1], STDOUT_FILENO);
            execlp("ls", "ls" , argv[1], NULL);
            exit(1);
        } else {
            dup2(fd2[1], STDIN_FILENO);
            dup2(fd1[0], STDOUT_FILENO);
            execlp("grep", "grep" , argv[2], fd1[0], NULL);
            exit(1);
        }
    } else {
        dup2(STDOUT_FILENO, tmp_stdout);
        dup2(fd2[0], STDIN_FILENO);
        execlp("sort", "sort" , fd2[0], NULL);
        exit(1);
    }

    exit(0);
}