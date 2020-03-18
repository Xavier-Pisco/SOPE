#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>

int v = 0;
bool crescent = true;

void sig_handler(int signo){
    if (signo == SIGUSR2) crescent = false;
    else crescent = true;
}

int main(void)
{
    srand(time(0));
    struct sigaction action;

    action.sa_handler = sig_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    pid_t pid;
    int n = 50, random;

    
    if (sigaction(SIGUSR1,&action,NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGUSR1 handler\n");
        exit(1);
    }
    if (sigaction(SIGUSR2,&action,NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGUSR2 handler\n");
        exit(1);
    }

    printf("Signals installed.\n");

    if ((pid = fork()) > 0){
        while(waitpid(-1, NULL, WNOHANG) == 0){
            random = (rand() % 2);
            if (random == 1){
                kill(pid, SIGUSR1);
            } else {
                kill(pid, SIGUSR2);
            }
            sleep(5);
        }
    } else {
        while(n > 0){
            if (crescent) v++;
            else v--;
            printf("%d\n", v);
            n--;
            sleep(1);
        }
    }
    exit(0);
} 