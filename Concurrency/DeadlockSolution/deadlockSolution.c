#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>


#define NUM_THREADS 5
#define NUM_MUTEXES 5

pthread_t philosophers[NUM_THREADS];
pthread_mutex_t forks[NUM_MUTEXES];
pthread_mutex_t waiter;

void * pick_up_forks_and_eat(void * philosopher_number)
{
    int fork_right = (int)philosopher_number;
    int fork_left = ((int)philosopher_number+1) % 5;
    while(1)
    {
        printf("philosopher %i is not eating \n", (int*)philosopher_number);
        pthread_mutex_lock(&waiter);
        printf("philosopher number %i is picking up fork to the right\n", (int*)philosopher_number);
        pthread_mutex_lock(&forks[fork_right]);
        printf("philosopher number %i is picking up fork to the left\n", (int*)philosopher_number);
        pthread_mutex_lock(&forks[fork_left]);
        pthread_mutex_unlock(&waiter);
        printf("philosopher number %i is eating for 1 second \n", (int*)philosopher_number);
        sleep(1);
        printf("philosopher number %i is putting down fork to the right\n", (int*)philosopher_number);
        pthread_mutex_unlock(&forks[fork_right]);
        printf("philosopher number %i is putting down fork to the left\n", (int*)philosopher_number);
        pthread_mutex_unlock(&forks[fork_left]);
    }
    return NULL;
}

/* bool ask_weither(int fork_right, int fork_left) */
/* { */
/*     bool r = 0; */
/*     printf("right fork: %i, left fork: %i \n", fork_right, fork_left); */
/*     if (forks[fork_right] != true)  && forks[&fork_left] != true) */
/*     { */
/*         r = 1; */
/*     } */
/*     return r; */
/* } */

int main()
{
    int i = 0;
    int error;

    if (pthread_mutex_init(&waiter, NULL) != 0)
    {
        printf("\n Mutex init has failed");
        return 1;
    }
    for (i = 0; i < NUM_MUTEXES; i++)
    {
        if (pthread_mutex_init(&forks[i],NULL) != 0)
        {
            printf("\n Mutex init has failed");
            return 1;
        }
    }

    for(i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&philosophers[i], NULL, &pick_up_forks_and_eat, (void *)i);
    }

    for(i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    for(i = 0; i < NUM_MUTEXES; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&waiter);

    return 0;
}
