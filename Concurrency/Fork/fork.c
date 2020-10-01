#include <stdio.h>
#include <unistd.h>

int b = 0;

/* int get_a() */
/* { */
/*     int a = 0; */
/*     return a; */
/* } */

int main()
{
    printf("main program entered\n");
    int a = 0;
    int i;

    for (i = 0; i < 10; ++i)
    {
        a += 1;
        b += 1;
    }
    printf("first loop finished\n");
    printf("a = %i \n", a);
    printf("b = %i \n", b);

    fork();
    printf("Child process created\n");

    for (i = 0; i < 10; ++i)
    {
        a += 1;
        b += 1;
    }
    printf("Second loop finished\n");
    printf("a = %i \n", a);
    printf("b = %i \n", b);
    printf("End of program reached\n");
    return 0;
}
