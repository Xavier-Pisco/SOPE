#include <stdio.h> 
#include <stdlib.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXELEMS 10000000 // nr. max de posicoes 
#define MAXTHREADS 100    // nr. max de threads 
#define min(a, b) (a)<(b)?(a):(b) 

int npos; 
int buf[MAXELEMS], pos=0, val=0;                // variaveis partilhadas 
sem_t sem;
char *shm;
int total = 0;

void fill() {
    while (1) {
        sem_wait(&sem);
        int k = (int) *shm--;
        val = (int)*shm--;
        pos = (int)*shm--;
        printf("fill %d\n", pos);
        if (pos >= npos) {
            return;
        }                 
        buf[pos] = val;
        pos++; 
        val++;
        k += 1;
        *shm++ = (char) pos;
        *shm++ = (char) val;
        *shm = (char)k;
        sem_post(&sem);
    }
} 

void verify() 
{
    sem_wait(&sem);
    *shm--;
    *shm--;
    pos = (int)*shm--;
    printf("verify %d\n", pos);
    for (int k = 0; k <= pos; k++){
        if (k <= pos && buf[k] != k)   // detecta valores errados
            printf("ERROR: buf[%d] = %d\n", k, buf[k]);
    }
    sem_post(&sem);
    return;
} 

int main(int argc, char *argv[]) {
    int k, nthr, count[MAXTHREADS];   // array para contagens
    int shmfd;

    if (argc != 3) {
        printf("Usage: %s <nr_pos> <nr_thrs>\n",argv[0]);
        return 1;
    }

    shmfd = shm_open("/smh", O_CREAT | O_RDWR, 0664);

    if (shmfd < 0){
        perror("Error creating shared mem\n");
        exit(2);
    } if (ftruncate(shmfd, 10) < 0){
        perror("Error in ftruncate()\n");
        exit(3);
    }

    shm = (char *) mmap(0,4,PROT_READ|PROT_WRITE,MAP_SHARED,shmfd,0);
    if(shm == MAP_FAILED)   {
        perror("WRITER failure in mmap()");
        exit(3);
    }

    *shm++ = (char) *buf;
    *shm++ = (char) pos;
    *shm++ = (char) val;

    sem_init(&sem, 0, 1);

    npos = min(atoi(argv[1]), MAXELEMS);    //no. efectivo de posicoes
    nthr = min(atoi(argv[2]), MAXTHREADS);  //no. efectivo de threads
    
    for (k=0; k<nthr; k++) {              
        count[k] = 0;
        if (fork() == 0){
            *shm = (char) k;
            fill();
            verify();
            printf("count[%d] = %d\n", k, count[k]);
            total += count[k];
            return 0;
        }
    }
    
    while(wait(NULL) > 0) continue;

    printf("total count = %d\n",total);   // mostra total         
    return 0; 
}