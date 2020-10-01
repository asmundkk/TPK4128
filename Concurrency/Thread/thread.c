#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int b = 0;

void * increment_n_times(int * iterations)
{
    int a = 0;
    int i;
    for (i = 0; i < *iterations; i++)
    {
        a += 1;
        b += 1;
    }
    printf("loop finished\n");
    printf("a = %i \n", a);
    printf("b = %i \n", b);
}

int main()
{
    printf("main program entered\n");
    /* int a = 0; */
    int iterations = 10;
    int n_threads = 2;
    pthread_t pthread[n_threads];

    increment_n_times(&iterations);

    int i;
    for (i = 0; i < n_threads; i++)
    {
        pthread_create(&pthread[i], NULL, &increment_n_times, &iterations);
        printf("thread created\n");
        pthread_join(pthread[i], NULL);
    }
    printf("end of program reached\n");
    return 0;
}
