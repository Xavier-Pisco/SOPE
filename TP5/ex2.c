#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>

struct number{
    char c;
    float f;
};

int main(){
    int a[2] = {0,0}, fd1[2], fd2[2];
    struct number n;

    pipe(fd1);
    pipe(fd2);

    if (fork() > 0){
        write(STDOUT_FILENO, "Write 2 numbers: ", 17);
        scanf("%d %d", &a[0], &a[1]);
        close(fd1[0]);
        close(fd2[1]);
        write(fd1[1], &a[0], 1);
        write(fd1[1], &a[1], 1);
        close(fd1[1]);
        
        while(read(fd2[0], &n, sizeof(n)) != 0){
            if (n.c == 'i')
                printf("%d\n", (int)n.f);
            else if (n.c == 'f')
                printf("%f\n", n.f);
            else
                printf("Operação inválida\n");
        }

    } else {
        close(fd1[1]);
        close(fd2[0]);
        read(fd1[0], &a[0], 1);
        read(fd1[0], &a[1], 1);
        n.f = a[0] + a[1];
        n.c = 'i';
        write(fd2[1], &n, sizeof(n));
        n.f = a[0] - a[1];
        n.c = 'i';
        write(fd2[1], &n, sizeof(n));
        n.f = a[0] * a[1];
        n.c = 'i';
        write(fd2[1], &n, sizeof(n));
        if (a[1] == 0){
            n.f = 0;
            n.c = 'x';
            write(fd2[1], &n, sizeof(n));
        } else if (a[0]%a[1] != 0){
            n.f = (float)a[0] / a[1];
            n.c = 'f';
            write(fd2[1], &n, sizeof(n));
        } else {
            n.f = a[0] / a[1];
            n.c = 'i';
            write(fd2[1], &n, sizeof(n));
        }
        close(fd1[0]);
    }

    exit(0);
}