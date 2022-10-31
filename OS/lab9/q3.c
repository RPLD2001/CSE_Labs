#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#define A_MEGABYTE 1024
int main()
{

    char *some_memory;
    int megabyte = A_MEGABYTE;
    int exit_code = EXIT_FAILURE;
    some_memory = (char *)malloc(megabyte);
    if (some_memory != NULL)
    {
        printf("Memory Allocated to some_memory is: %d\n", megabyte);
        sprintf(some_memory, "Hello World\n");
        printf("%s", some_memory);
        free(some_memory);
        printf("Memory freed free()\n");
        exit_code = EXIT_SUCCESS;
        exit(exit_code);
    }
}