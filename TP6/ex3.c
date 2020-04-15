#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define NUM_THREADS 10 

void *PrintHello(void *threadnum) {
    printf("Hello from thread no. %d!\n", *(int *) threadnum);    
    pthread_exit(NULL);
} 
    
int main() {    
    pthread_t threads[NUM_THREADS];    
    int t[NUM_THREADS];    
    for(int i=0; i< NUM_THREADS; i++) {     
        t[i] = i;  
        printf("Creating thread %d\n", i);       
        pthread_create(&threads[i], NULL, PrintHello, (void *)&t[i]);    
    }    
    pthread_exit(0); 
}