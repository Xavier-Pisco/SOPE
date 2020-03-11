#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    int status;

    if (argc != 2) {
        printf("usage: %s dirname\n",argv[0]);
        exit(1);
    }

    pid=fork();

    if (pid > 0)
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);

    else if (pid == 0){
        char *arg[] = {"ls", "-laR", argv[1], NULL};
        execve("/bin/ls", arg, envp);
        printf("Command not executed !\n");
        exit(1);
    }

    printf("Got here\n");
    wait(&status);
    printf("Child exited with value %d\n", status);
    exit(0);
}
