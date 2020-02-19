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
    
    printf("Hello %s \n", getenv("USER_NAME"));

    return 0;
}
