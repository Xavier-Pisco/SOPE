#include "stdio.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    printf("1\n");
    if (fork() > 0){
        printf("2");printf("3");
    } else {
        printf("4");
        printf("5");
    }
    printf("\n");
    return 0;
}