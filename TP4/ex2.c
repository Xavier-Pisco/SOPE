#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void sigterm_hanlder(int signo){
    printf("Entering SIGTERM handler ...\n");
    sleep(5);
    printf("Exiting SIGTERM handler ...\n");
}

void sigint_handler(int signo)
{
    printf("Entering SIGINT handler ...\n");
    sleep(5);
    printf("Exiting SIGINT handler ...\n");
} 

int main(void)
{
    struct sigaction action_int, action_term;

    action_int.sa_handler = sigint_handler;
    sigemptyset(&action_int.sa_mask);
    action_int.sa_flags = 0;

    if (sigaction(SIGINT,&action_int,NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGINT handler\n");
        exit(1);
    }

    action_term.sa_flags = 0;
    sigemptyset(&action_term.sa_mask);
    action_term.sa_handler = sigterm_hanlder;

    if (sigaction(SIGTERM,&action_term,NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGTERM handler\n");
        exit(1);
    }

    printf("Try me with CTRL-C ...\n");

    while(1) pause();

    exit(0);
} 