#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUF_LENGHT 256

int main(int argc, char* argv[]){
    FILE *src, *dst;
    char buf[BUF_LENGHT];

    if (argc < 2){
        printf("usage: ex6 file1 file2\n");
        return -1;
    }

    if ((src = fopen(argv[1], "r")) == NULL){
        perror(strerror(errno));
        exit(1);
    }
    if ((dst = fopen(argv[2], "w")) == NULL){
        perror(strerror(errno));
        exit(2);
    }
    while((fgets(buf, BUF_LENGHT, src)) != NULL){
        fputs(buf ,dst);
    }
    fclose(src);
    fclose(dst);
    exit(0);

}