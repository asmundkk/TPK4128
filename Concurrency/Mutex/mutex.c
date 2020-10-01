#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>
#include<semaphore.h>
#include<unistd.h>

bool running = 1;
int var1 = 0;
int var2 = 0;

pthread_mutex_t mutex1;


void * increment()
{
    while(running ==1)
    {
        pthread_mutex_lock(&mutex1);
        var1 += 1;
        var2 = var1;
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}

void * print_variables()
{
    int i;
    for(i = 0; i < 20; i++)
    {
        printf("Number 1: %i, number 2: %i, difference: %i \n", var1, var2, var1-var2);
        sleep(1);
    }
    running = 0;
    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL, &increment, NULL);
    pthread_create(&thread2, NULL, &print_variables, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}
