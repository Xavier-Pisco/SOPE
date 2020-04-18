#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_STRING_SIZE 512

struct number{
    char c;
    float f;
};

int main(){
    int a[2] = {0,0}, fd1, fd2;
    struct number n;
    char fifo_name[MAX_STRING_SIZE];

    sprintf(fifo_name, "/tmp/fifo_ans_%d", getpid());
    mkfifo(fifo_name, 0644);
    
    while((fd1 = open("/tmp/fifo_req", O_WRONLY)) == -1){
        sleep(1);
    }


    while (1){
        write(STDOUT_FILENO, "Write 2 numbers (0, 0 to leave): ", 33);
        scanf("%d %d", &a[0], &a[1]);
        write(fd1, fifo_name, strlen(fifo_name) + 1);
        sleep(1);
        write(fd1, &a[0], 1);
        write(fd1, &a[1], 1);
        fd2 = open(fifo_name, O_RDONLY);
        
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
        close(fd2);
    }

    close(fd1);
    unlink(fifo_name);

    return 0;
}