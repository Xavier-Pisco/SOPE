#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int a, b, fd[2];

    pipe(fd);

    if (fork() > 0){
        write(STDOUT_FILENO)
    }

}