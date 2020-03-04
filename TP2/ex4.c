#include "termios.h"
#include "unistd.h"
#include "stdio.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_NAME_LEN 50

int main(int argc, char* argv[]){
    int f1, nr, note;
    char name[50];

    if (argc != 2){
        printf("Usage: %s file", argv[0]);
        return 1;
    }

    f1 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (f1 == -1){
        perror(argv[1]);
        return 2;
    }

    while((nr = read(STDIN_FILENO, &name, sizeof(name))) > 1){
        write(f1, &name, nr);
        nr = read(STDIN_FILENO, &note, sizeof(int));
        write(f1, &note, nr);
    }

    close(f1);

    return 0;
}