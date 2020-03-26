#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[], char* envp[]){
    int fd1[2], fd2[2];

    if (argc != 3){
        printf("Usage: %s directory string\n", argv[0]);
        exit(1);
    }

    if (pipe(fd1) != 0){
        printf("Error creating pipe\n");
        exit(2);
    }
    if (pipe(fd2) != 0){
        printf("Error creating pipe\n");
        exit(2);
    }
    

    if (fork() > 0){
        if (fork() > 0){
            close(fd2[0]);
            close(fd2[1]);
            close(fd1[0]);
            dup2(fd1[1], STDOUT_FILENO);
            execlp("ls", "ls", argv[1], "-laR", NULL);
        } else {
            close(fd1[1]);
            close(fd2[0]);
            dup2(fd1[0], STDIN_FILENO);
            dup2(fd2[1], STDOUT_FILENO);
            execlp("grep", "grep", argv[2], NULL);
        }
    } else {
        close(fd2[1]);
        close(fd1[0]);
        close(fd1[1]);
        dup2(fd2[0], STDIN_FILENO);
        execlp("sort", "sort", NULL);
    }

    exit(3);
}