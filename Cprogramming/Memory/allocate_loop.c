#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void allocate(int value) {

    int *ptr = NULL;
    ptr = malloc(100000 * sizeof(int));

    *ptr = value;

    printf("test of allocated memory: %i\n");

    free(value);

    if(&value != NULL)
    {
        perror("Memory Error Detected: The memory is not freed after allocation");
        errno = 0;
        /* return(-1); */
    }
}

int main() {

    int a = 1;

    while(a < 2 ){

        allocate(a);
        if (errno==0)
        {
            break;
        }
    }

}
