#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    if (argc < 2){
        printf("Usage %s cmd1 cmd2 ...", argv[0]);
        exit(1);
    }

    pid_t pids[argc - 1];
    int status, pid;

    for (int i = 0; i < argc - 1; i++){
        if ((pids[i] = fork()) > 0){
            sleep(1);
        } else {
            execlp(argv[i + 1], NULL);
            exit(1);
        }
    }

    while( (pid = wait(&status)) > 0){
        if (WEXITSTATUS(status) != 0){
            for (int i = 0; i < argc - 1; i++){
                kill(pids[i], SIGTERM);
            }
        }
        printf("Child %d with exit %d", pid, WEXITSTATUS(status));
    }

    exit(0);
}