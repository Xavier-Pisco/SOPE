#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>

int main(){
    int a[2] = {0,0}, fd[2];

    pipe(fd);

    if (fork() > 0){
        write(STDOUT_FILENO, "Write 2 numbers: ", 17);
        scanf("%d %d", &a[0], &a[1]);
        close(fd[0]);
        write(fd[1], &a[0], 1);
        write(fd[1], &a[1], 1);
        close(fd[1]);
        wait(NULL);
    } else {
        close(fd[1]);
        while(read(fd[0], &a[0], 1) < 1){
            sleep(1);
        }
        while(read(fd[0], &a[1], 1) < 1){
            sleep(1);
        }
        printf("%d %d\n", a[0], a[1]);
        printf("Soma: %d\n", a[0] + a[1]);
        printf("Subtração: %d\n", a[0] - a[1]);
        printf("Multiplicação: %d\n", a[0] * a[1]);
        if (a[1] == 0){
            printf("Não é possivel a divisão\n");
        } else {
            printf("Divisão: %d\n", a[0]/a[1]);
        }
        close(fd[0]);
    }

    exit(0);
}