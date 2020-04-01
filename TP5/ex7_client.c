#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

struct number{
    char c;
    float f;
};

int main(){
    int a[2] = {0,0}, fd1, fd2;
    struct number n;

    mkfifo("/tmp/fifo_req",0660);
    mkfifo("/tmp/fifo_ans", 0660);

    fd1 = open("/tmp/fifo_req", O_WRONLY);
    fd2 = open("/tmp/fifo_ans", O_RDONLY);

    while (1){
        write(STDOUT_FILENO, "Write 2 numbers (0, 0 to leave): ", 33);
        scanf("%d %d", &a[0], &a[1]);
        write(fd1, &a[0], 1);
        write(fd1, &a[1], 1);
        
        if (a[0] == 0 && a[1] == 0) break;

        for (int i = 0; i < 4; i++){
            read(fd2, &n, sizeof(n));
            if (n.c == 'i')
                printf("%d\n", (int)n.f);
            else if (n.c == 'f')
                printf("%f\n", n.f);
            else
                printf("Operação inválida\n");
        }
    }

    return 0;
}