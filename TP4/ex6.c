#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t pid = 0;

void alarmhandler(int signo){
    kill(pid, SIGKILL);
}

int main(int argc, char* argv[]){

    if (argc < 3){
        printf("Usage %s t prog prog_arg1 prog_arg2 ...", argv[0]);
        exit(1);
    }

    int time = atoi(argv[1]);
    int status;


    if ((pid = fork()) > 0){
        signal(SIGALRM, alarmhandler);
        alarm(time);
        wait(&status);
        if (WIFEXITED(status)){
            printf("Normal exit\n");
        } else {
            printf("Abnormal exit\n");
        }
    } else {
        execv(argv[2], &argv[2]);
    }


    exit(0);
}