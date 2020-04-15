#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct numbers {
    int n1, n2;
};

void * soma(void * n){
    struct numbers *numbers = (struct numbers *) n;
    int final = numbers->n1 + numbers->n2;

    void * ret = malloc(sizeof(int));
    *(int *)ret = final;
    return ret;
}

void * subtracao(void * n){
    struct numbers *numbers = (struct numbers *) n;
    int final = numbers->n1 - numbers->n2;

    void * ret = malloc(sizeof(int));
    *(int *)ret = final;
    return ret;
}

void * multiplicacao(void * n){
    struct numbers *numbers = (struct numbers *) n;
    int final = numbers->n1 * numbers->n2;

    void * ret = malloc(sizeof(int));
    *(int *)ret = final;
    return ret;
}

void * divisao(void * n){
    struct numbers *numbers = (struct numbers *) n;
    float final;
    if (numbers->n2 == 0) final = 0;
    else final = numbers->n1*1.0 / numbers->n2;

    void * ret = malloc(sizeof(float));
    *(float *)ret = final;
    return ret;
}

int main(){
    pthread_t threads[4];
    struct numbers numbers;
    void * status;
    write(STDOUT_FILENO, "Write 2 numbers (0, 0 to leave): ", 33);
    scanf("%d %d", &numbers.n1, &numbers.n2);

    pthread_create(&threads[0], NULL, soma, (void *) &numbers);
    pthread_create(&threads[1], NULL, subtracao, (void *) &numbers);
    pthread_create(&threads[2], NULL, multiplicacao, (void *) &numbers);
    pthread_create(&threads[3], NULL, divisao, (void *) &numbers);

    for (int i = 0; i < 3; i++){
        pthread_join(threads[i], &status);
        printf("%d\n", * (int *) status);
    }

    pthread_join(threads[3], &status);
    printf("%f\n", * (float *) status);

    pthread_exit(0);
}