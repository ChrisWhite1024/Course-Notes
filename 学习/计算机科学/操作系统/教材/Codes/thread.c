#include <stdio.h>
#include <stdlib.h> /* Perform standard utility functions like dynamic memory allocation, using functions such as malloc() and calloc(). */
#include <pthread.h>

volatile int counter = 0; /* Ignore this variable from compiler optimizations. */
int loops;

/* Return a NULL pointer (void pointer), and do. void *arg argument refers to an expected 
input of a pointer of any type. Not sure why it's specified if the arg variable is never mentioned again.*/
void *worker(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        counter++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    /* Ensure that the user inputs an argument after the program name. */
    if (argc != 2) {
        fprintf(stderr, "usage: threads <value\n");
        exit(1);
    }
    loops = atoi(argv[1]); /* Converts a string argument into the ASCII integer equivalent. */
    pthread_t p1, p2; /* Threads wi */
    printf("Initial value : %d\n", counter);

    /* Both threads that are created access the same function and counter variable. 
    The lesson here was that for higher numbers, you'll notice that the counter isn't 
    just 2N, and instead you may get random numbers. Thats because the counter increment process 
    in the function (steps: load counter variable from memory, increment it, and save it, doesn't happen 
    atomically (all at once). */
    pthread_create(&p1, NULL, worker, NULL);    
    pthread_create(&p2, NULL, worker, NULL);    
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("Final value : %d\n", counter);

    return 0;
}
