#include <stdio.h> 
#include <stdlib.h>
#include "string.h"

int ex4(int argc, char* argv[]) {

    for (int i = 0; i < atoi(argv[2]); i++){
        printf("Hello %s! \n", argv[1]);
    }

    return 0;
}

int main(int argc, char* argv[], char* envp[]){
    int i = 0;
    
    while(envp[i] != NULL){
        if (!strncmp("USER=", envp[i], 5))
            printf("Hello %s \n",envp[i]);
        i++;
    }

    return 0;
}