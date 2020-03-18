#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


int main(void)
{
    int i, n;
    struct sigaction action;

    action.sa_handler = SIG_IGN;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    

    for (i=1; i<=3; i++) { 
        if (fork() == 0){
            printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
            sleep(i*7); // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
            raise(SIGCHLD);
            exit(0);
        } else {
            if (sigaction(SIGCHLD,&action,NULL) < 0)
            {
                fprintf(stderr,"Unable to install SIGCHLD handler\n");
                exit(1);
            }
        }
    }

    for (i=1 ;i<=4; i++ ) {
        
            
        printf("PARENT: working hard (task no. %d) ...\n",i);
        n=20; while((n=sleep(n))!=0);
        
        printf("PARENT: end of task no. %d\n",i);
    }
    exit(0);
}