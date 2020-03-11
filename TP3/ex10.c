#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    int status;

    if (argc != 2 && argc != 3) {
        printf("usage: %s dirname\n",argv[0]);
        printf("usage: %s dirname file\n", argv[0]);
        exit(1);
    }

    pid=fork();

    if (pid > 0)
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);

    else if (pid == 0){
        if (argc == 3){
            int f1 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (f1 == -1){
                perror(argv[2]);
                exit(2);
            }
            dup2(f1, STDOUT_FILENO);
        }

        char *arg[] = {"ls", "-laR", argv[1], NULL};
        execve("/bin/ls", arg, envp);
        printf("Command not executed !\n");
        exit(1);
    }
    
    wait(&status);
    if (WIFEXITED(status)){
        printf("Exited normally with status %d\n", status);
    } else if (WIFSIGNALED(status)){
        printf("Exited abnormally with status %d\n", status);
    }
    exit(0);
}
