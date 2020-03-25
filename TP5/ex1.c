#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>

#define MAX_SIZE 50

struct twoints{
    char a[MAX_SIZE], b[MAX_SIZE];
};

int main(){
    int fd[2];
    struct twoints ints;

    pipe(fd);

    if (fork() > 0){
        write(STDOUT_FILENO, "Write 2 numbers: ", 17);
        scanf("%s %s", ints.a, ints.b);
        close(fd[0]);
        write(fd[1], &ints, sizeof(ints));
        close(fd[1]);
        wait(NULL);
    } else {
        close(fd[1]);
        read(fd[0], &ints, sizeof(ints));
        int a = atoi(ints.a), b = atoi(ints.b);
        printf("Soma: %d\n", a + b);
        printf("Subtração: %d\n", a - b);
        printf("Multiplicação: %d\n", a * b);
        if (b == 0){
            printf("Não é possivel a divisão\n");
        } else {
            printf("Divisão: %d\n", a/b);
        }
        close(fd[0]);
    }

    exit(0);
}