#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define N 10

void * threadFunc(void * threadnum){
    sleep(1);
    printf("Thread %d\n", *(int *) threadnum);
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
}