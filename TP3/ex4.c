#include "termios.h"
#include "unistd.h"
#include "stdio.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){

    pid_t pid;

    if ((pid = fork()) > 0){
        write(STDOUT_FILENO, "Hello ", 7);
    } else {
        write(STDOUT_FILENO, "World\n", 7);
    }

    if (pid <= 0){
        write(STDOUT_FILENO, "Hello ", 7);
    } else {
        write(STDOUT_FILENO, "World\n", 7);
    }

    write(STDOUT_FILENO,"\n",1);
    return 0;
}