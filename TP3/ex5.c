#include "termios.h"
#include "unistd.h"
#include "stdio.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){

    pid_t ppid, fpid;

    if ((ppid = fork()) > 0){
        write(STDOUT_FILENO, "Hello ", 7);
    } else {
        if ((fpid = fork()) > 0){
            write(STDOUT_FILENO, "my ", 3);
        } else {
            write(STDOUT_FILENO, "friends!\n", 9);
        }
    }
    return 0;
}