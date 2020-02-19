#include <stdlib.h>
#include <stdio.h>

void exit1(){
    printf("Executing exit handler 1\n");
    exit(0);
}

void exit2(){
    printf("Executing exit handler 2\n");
    exit(0);
}

int main(){
    atexit(exit1);

    atexit(exit2);
    
    printf("Main done!\n");
    abort();
    exit(0);
}