#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <pthread.h>

void *sleep_and_print()
{
    int sec;
    sec = 5;
    /* sec = (int)seconds; */
    printf("Sleeping for %i seconds\n", sec);
    sleep(sec);
    printf("Done sleeping\n");
}

void *busy_wait_delay(int *seconds)
{
    int i, dummy;
    int tps = sysconf(_SC_CLK_TCK);
    clock_t start;
    struct tms exec_time;

    printf("Sleeping for %i seconds\n", *seconds);
    times(&exec_time);
    start = exec_time.tms_utime;

    while( (exec_time.tms_utime - start) < (*seconds * tps))
    {
        for(i=0; i<1000; i++)
        {
            dummy = i;
        }
        times(&exec_time);
    }
    printf("Done sleeping\n");
}

int main()
{
    pthread_t pthreads[2];
    /* int rc; */
    int i;
    int seconds = 5;
    for (i = 0; i < 2; i++)
    {
        printf("creating thread for busy delay wait %i \n", i);
        /* pthread_create(&pthreads[i], NULL, sleep_and_print, NULL); */
        pthread_create(&pthreads[i], NULL, busy_wait_delay, &seconds);
    }
    pthread_exit(NULL);
    /* pthread_create() */
    /* sleep_and_print(5); */
    /* sleep_and_print(5); */
    /* busy_wait_delay(5); */
    /* busy_wait_delay(5); */
}
