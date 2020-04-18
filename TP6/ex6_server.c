#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 512

struct number{
    char c;
    float f;
};

int main(){
    int a[2] = {0,0}, fd1, fd2;
    struct number n;
    char fifo_name[MAX_STRING_SIZE];

    mkfifo("/tmp/fifo_req", 0644);

    while((fd1 = open("/tmp/fifo_req", O_RDONLY)) == -1){
        sleep(1);
    }

    while(true) {
        int nread;
        while ((nread = read(fd1, fifo_name, MAX_STRING_SIZE)) <= 0) sleep(1);
        if ((fd2 = open(fifo_name, O_WRONLY)) == -1) return 1;
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

        close(fd2);
    }

    unlink("/tmp/fifo_req");
    return 0;
}