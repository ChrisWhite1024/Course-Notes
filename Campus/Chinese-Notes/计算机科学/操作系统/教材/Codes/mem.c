#include <stdio.h> /* Used to perform input and output operations in C like scanf() and printf(). */
#include <stdlib.h> /* Perform standard utility functions like dynamic memory allocation, using functions such as malloc() and calloc(). */
#include <unistd.h> /* Module that is required for the sleep function. */
#include <assert.h>

int main(int argc, char *argv[]) {
    int *p = malloc(sizeof(int)); /* Define the pointer variable and assign it the address of the reserved memory location. */
    assert(p != NULL); /* Good practice to ensure that the memory was allocated properly. */
    /* %d format specifier: Print the next argument as an int, %p: Print the next argument as a pointer address.*/
    printf("(%d) address pointed to by p: %p\n", getpid(), p);
    *p = 0; /* Dereference the pointer variable and assign the variable stored at that address. */
    while (1) {
        sleep(1);
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p);
    }
    return 0;
}
