#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int count = 0;
#define COUNT_MAX 10

pthread_mutex_t mutexsum;

void *countSum(void *tid)
{
    long id = (long)tid;

    while (count < COUNT_MAX)
    {
        pthread_mutex_lock(&mutexsum);
        count = count + 1;
        printf("Thread %ld: contador em %d\n", id, count);
        pthread_mutex_unlock(&mutexsum);

        sleep(rand() % 3);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2, t3; // criando t1 e t2 do tipo thread
    int create;           // variável que recebe o retorno da função pthread_create()
    long num;             // identificador da thread

    pthread_mutex_init(&mutexsum, NULL);
    num = 1;
    printf("Main: criando a thread %ld\n", num);
    create = pthread_create(&t1, NULL, countSum, (void *)num); // criando thread 1

    num = 2;
    printf("Main: criando a thread %ld\n", num);
    create = pthread_create(&t2, NULL, countSum, (void *)num); // criando thread 2

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Main: finalizando\n");

    pthread_mutex_destroy(&mutexsum);

    return 0;
}
