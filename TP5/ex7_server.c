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

    while((fd1 = open("/tmp/fifo_req", O_RDONLY)) == -1){
        sleep(1);
    }
    while((fd2 = open("/tmp/fifo_ans", O_WRONLY)) == -1){
        sleep(1);
    }
    printf("Opened\n");

    while (1) {
        read(fd1, &a[0], 1);
        read(fd1, &a[1], 1);
        if (a[0] == 0 && a[1] == 0) break;
        n.f = a[0] + a[1];
        n.c = 'i';
        write(fd2, &n, sizeof(n));
        n.f = a[0] - a[1];
        n.c = 'i';
        write(fd2, &n, sizeof(n));
        n.f = a[0] * a[1];
        n.c = 'i';
        write(fd2, &n, sizeof(n));
        if (a[1] == 0){
            n.f = 0;
            n.c = 'x';
            write(fd2, &n, sizeof(n));
        } else if (a[0]%a[1] != 0){
            n.f = (float)a[0] / a[1];
            n.c = 'f';
            write(fd2, &n, sizeof(n));
        } else {
            n.f = a[0] / a[1];
            n.c = 'i';
            write(fd2, &n, sizeof(n));
        }
    }
}