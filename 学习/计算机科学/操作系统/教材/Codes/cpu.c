#include <stdio.h> /* Used to perform input and output operations in C like scanf() and printf(). */
#include <stdlib.h> /* Perform standard utility functions like dynamic memory allocation, using functions such as malloc() and calloc(). */
#include <sys/time.h> /* Provides you with time types */
#include <assert.h> /* This gives you the assert functionality to test your code. */
#include <unistd.h> /* Module that is required for the sleep function. */

/* argc is the number of arguments passed into the program, and argv is the list of arguments that were passed in.*/
int main(int argc, char *argv[]) {
    /* 
    Validate that the user has passed in 1 argument (the first argument by default is the programs name)
    Print the passed in argument to the console.
    */

    if (argc != 2) {
        /* fprintf prints to a file, while printf prints to the console.*/
        fprintf(stderr, "usage: cpu <string>\n"); /* With fprintf you also have to specify the location you want to print - in this case the stderr.*/
        exit(1);
    }
    char *str = argv[1];
    while (1) {
        sleep(1);
        printf("%s\n", str);
    }
    return 0;
}
