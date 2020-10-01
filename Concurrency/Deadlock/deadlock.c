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

void * pick_up_forks_and_eat(void * philosopher_number)
{
    while(1)
    {
        printf("philosopher %i is not eating", (int*)philosopher_number);
        int fork_right = (int)philosopher_number;
        int fork_left = ((int)philosopher_number+1) % 5;
        printf("right fork: %i, left fork: %i \n", fork_right, fork_left);

        printf("philosopher number %i is picking up fork to the right\n", (int*)philosopher_number);
        pthread_mutex_lock(&forks[fork_right]);
        printf("philosopher number %i is picking up fork to the left\n", (int*)philosopher_number);
        pthread_mutex_lock(&forks[fork_left]);
        printf("philosopher number %i is teating for 1 second \n", (int*)philosopher_number);
        sleep(2);
        printf("philosopher number %i is putting down fork to the right\n", (int*)philosopher_number);
        pthread_mutex_unlock(&forks[fork_right]);
        printf("philosopher number %i is putting down fork to the left\n", (int*)philosopher_number);
        pthread_mutex_unlock(&forks[fork_left]);
    }
    return NULL;
}

int main()
{
    int i = 0;
    int error;

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

    return 0;
}
