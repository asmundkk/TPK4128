#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

sem_t semaphore; //an atomic unsigned int
sem_t * p_semaphore = &semaphore; // pointer to the semaphore

void * resource(void * thread_number)
{
    sem_wait(p_semaphore);
    int i;
    for (i = 0; i < 4; i++)
    {
        printf("Thread number %i \n", (int *)thread_number);
        usleep(1000000);
    }
    sem_post(p_semaphore);
}
int main()
{
    int num_threads = 5;
    pthread_t thread[num_threads];

    /* pointer to the semaphore that is initializded,  */
    /* O means that the semaphore is shared between threads */
    /* 1 is the integer value. */
    sem_init(p_semaphore, 0, 3);

    int i;
    for(i = 0; i < num_threads; i++)
    {
        pthread_create(&thread[i], NULL, &resource, (void*) i);
    }
    for (i = 0; i < num_threads; i++)
    {
        pthread_join(thread[i], NULL);
    }

    return 0;
}
