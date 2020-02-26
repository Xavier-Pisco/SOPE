#include "termios.h"
#include "unistd.h"
#include "stdio.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READ_SIZE 50

int _2_a(int argc, char* argv[]){

    if (argc != 3){
        printf("Usage: copy file1 file2 \n");
        return 1;
    }

    FILE *f1, *f2;

    f1 = fopen(argv[1], "r");
    if (f1 == NULL){
        perror(argv[1]);
        return 2;
    }

    f2 = fopen(argv[2], "w");
    if (f2 == NULL){
        perror(argv[2]);
        fclose(f1);
        return 3;
    }

    char s[READ_SIZE];
    int nr;
    while(!feof(f1)){
        nr = fread(s,1,READ_SIZE,f1);
        fwrite(s,1,nr,f2);
    }
    fclose(f1);
    fclose(f2);

    return 0;
}

int main(int argc, char* argv[]){

    if (argc != 3){
        printf("Usage: copy file1 file2 \n");
        return 1;
    }

    int f1, f2, nr;
    char s[READ_SIZE];
    
    f1 = open(argv[1],O_RDONLY);
    if (f1 == -1){
        perror(argv[1]);
        return 2;
    }

    f2 = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if (f2 == -1){
        perror(argv[2]);
        return 2;
    }

    while((nr = read(f1,s,READ_SIZE))){
        if (nr == -1) break;
        write(f2,s,nr);
    }

    close(f1);
    close(f2);

    return 0;
} 