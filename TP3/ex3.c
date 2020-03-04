#include "termios.h"
#include "unistd.h"
#include "stdio.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define MAX 500


int main(){
    int i;
    pid_t pid;
    char str[10];

    pid = fork();
    switch(pid) {
        case -1:
            perror("fork");
            return 1;
        case 0:
            for (i=1; i<=MAX; i++) {
                sprintf(str,"-%d",i);
                write(STDOUT_FILENO,str,strlen(str));
            }
            break;
        default:
            for (i=1; i<=MAX; i++) {
                sprintf(str,"+%d",i);
                write(STDOUT_FILENO,str,strlen(str));
            }
    }
    return 0;
}