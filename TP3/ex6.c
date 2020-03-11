#include "termios.h"
#include "unistd.h"
#include "stdio.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(void) {  
    pid_t pid;
    struct rlimit limit;
    int i;
    printf("I'm process %d. My parent is %d.\n", getpid(),getppid());  
    for (i=1; i<=3; i++) {
        pid = fork();        
        if ( pid < 0) {                   
            printf("fork      error");                        
            exit(1);             }        
        else if (pid == 0) {              
            printf("I'm process %d. My parent is %d. I'm going to work for 1 second ...\n", getpid(),getppid());              
            sleep(1);  // simulando o trabalho do filho              
            printf("I'm process %d. My parent is %d. I finished my work\n", getpid(),getppid());
            exit(0);  // a eliminar na alinea c)        
            }        
        else{            // simulando o trabalho do pai                   
            while (waitpid(0, NULL, WNOHANG) == 0){
                sleep(0.5);
            }
        }
    }
    getrlimit(RLIMIT_NPROC, &limit);
    printf("%lu\n", limit.rlim_cur);
    printf("%lu\n", limit.rlim_max);
    exit(0);
}