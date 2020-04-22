#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MAX_STRING_SIZE 512
#define MAX_NUMBERS 50

struct FileString{
    char* file;
    char* string;
};

void *readfile(void *args){

    struct FileString *fs = (struct FileString *) args;
    FILE *f;
    int i = 1, n = 0;
    char string[MAX_STRING_SIZE];
    int *numbers = malloc(MAX_NUMBERS);

    if ((f = fopen(fs->file, "r")) == NULL){
        perror(fs->file);
        exit(2);
    }

    while(fgets(string, MAX_STRING_SIZE, f) && n < 50){
        char * word = strtok(string , " \n");
        while(word != NULL){
            if (strcmp(word, fs->string) == 0){
                numbers[n++] = i;
            }
            word = strtok(NULL , " \n");
        }
        i++;
    }
    return (void *) numbers;
}

int main(int argc, char* argv[]){

    if (argc < 3){
        printf("Usage: %s string file1 file2...", argv[0]);
        exit(1);
    }

    pthread_t threads[argc - 2];

    for (int i = 0; i < argc - 2; i++){
        struct FileString *args = malloc(sizeof(struct FileString *));
        args->file = argv[2 + i];
        args->string = argv[1];
        pthread_create(&threads[i], NULL, readfile, (void *) args);
    }

    for (int i = 0; i < argc - 2; i++){
        void * ret = malloc(sizeof(void *));
        pthread_join(threads[i], &ret);
        int * numbers = (int *) ret;
        int n = 0;
        printf("%s\n", argv[2 + i]);
        while(numbers[n] != NULL){
            printf("%d\n", numbers[n++]);
        }
        if (n == 0){
            printf("'%s' not found\n", argv[1]);
        }
    }

    pthread_exit(0);
}