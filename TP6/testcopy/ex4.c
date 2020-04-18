#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define N 10

void * threadFunc(void * threadnum){
    sleep(1);
    printf("Thread %lu\n", pthread_self());
    return threadnum;
}

int main(){
    pthread_t threads[N];    
    int t[N];    
    void * status;
    for(int i=0; i< N; i++) {     
        t[i] = i;  
        printf("Creating thread %d\n", i);       
        pthread_create(&threads[i], NULL, threadFunc, (void *)&t[i]);
    }    
    
    for (int i = 0; i < N; i++){
        pthread_join(threads[i], &status);
        printf("Exit code %d\n", * (int *) status);
    }

    pthread_exit(0); 
}("%d\n%d\n", *(int *) r1, *(int *) r2);

    return 0;
}        write(fd1, &a[1], 1);
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