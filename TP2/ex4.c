#include "termios.h"
#include "unistd.h"
#include "stdio.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_NAME_LEN 50

struct Student{
    char name[MAX_NAME_LEN];
    int note;
};

int main(int argc, char* argv[]){
    int f1, nr;
    struct Student student;

    if (argc != 2 && argc != 3){
        printf("Usage: %s file", argv[0]);
        return 1;
    }

    if (argc == 2){
        f1 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (f1 == -1){
            perror(argv[1]);
            return 2;
        }

        while((nr = read(STDIN_FILENO, &student.name, sizeof(student.name))) > 1){
            nr += read(STDIN_FILENO, &student.note, sizeof(int));
            write(f1, &student, nr);
        }
    }

    else {
        f1 = open(argv[1], O_RDONLY);
        if (f1 == -1){
            perror(argv[1]);
            return 2;
        }
        write(STDOUT_FILENO, "Start reading\n", 15);
        while((nr = read(f1, &student, sizeof(student))) > 0){
            write(STDOUT_FILENO, &student.name, sizeof(student.name));
            write(STDOUT_FILENO, &student.note, sizeof(int));
        }
        write(STDOUT_FILENO, "Ended reading\n", 15);    
    }
    
    close(f1);

    return 0;
}