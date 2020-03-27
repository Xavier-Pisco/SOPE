#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARG_SIZE 20

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Usage %s cmd1 arg1 | cmd2 ...\n", argv[0]);
        exit(1);
    }

    int fd_numbers = 0;

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "|")){
            fd_numbers++;
        }
    }

    int fd[fd_numbers][2], i = 1, n = 0;


    char* args[MAX_ARG_SIZE];
    
    while(i < argc){
        pipe(fd[n]);
        int j = 0;
        
        while(strcmp(argv[i], "|") && i < argc){
            i++;
            args[j++] = argv[i];
        }
        args[j] = NULL;

        if (fork()){
            close(fd[n][1]);
            close(fd[n-1][0]);
            close(fd[n-1][1]);
        } else {
            if (n == 0){
                close(fd[n][0]);
                dup2(fd[n][1], STDOUT_FILENO);
                execvp(args[0], &args[0]);
            }
            else if (i != argc){
                close(fd[n][0]);
                dup2(fd[n-1][0], STDIN_FILENO);
                dup2(fd[n][1], STDOUT_FILENO);
                execvp(args[0], &args[0]);
            } else {
                close(fd[n][1]);
                close(fd[n][0]);
                dup2(fd[n-1][0], STDIN_FILENO);
            }
        }
        n++;
    }


    exit(0);
}