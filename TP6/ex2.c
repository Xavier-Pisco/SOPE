#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR 2

int num_iter = 5000;
    
void * thrfunc(void * arg) {
    int i = 0;
    fprintf(stderr, "Starting thread %s\n", (char *) arg);

    while(num_iter > 0){
        write(STDERR, arg, 1);
        num_iter--;
        i++;
    }
    void * ret = malloc(sizeof(int));
    *(int *) ret = i;
    return ret;
}


int main() {
    pthread_t ta, tb;
    void *r1, *r2;

    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");
    pthread_join(ta, &r1);
    pthread_join(tb, &r2);

    write(STDERR, "\n", 1);
    printf("%d\n%d\n", *(int *) r1, *(int *) r2);

    return 0;
}