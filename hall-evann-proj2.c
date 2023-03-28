#include <stdlib.h> // Required for rand()
#include <stdio.h>
#include "circularqueue.h"



int main(int argc, char *argv[]) {
    CircularQueue q;

   
    
    // Initialize any required variables and the buffer

    // Create the producer and consumer threads using pthread_create()

    // Join the threads using pthread_join()

    return 0;
}

/*
void *producer(void *param) {
    int item;

    while (1) {
        // Sleep for a random period of time
        sleep(3);

        // Generate a random number
        item = rand();

        if (insert_item(item))
            //
            printf("g");
        else
            printf("producer produced %d\n", item);
    }
}

void *consumer(void *param) {
    int item;

    while (1) {
        // Sleep for a random period of time
        sleep(3);

        if (remove_item(&item))
            printf("g");
            //fprintf("report error condition");
        else
            printf("consumer consumed %d\n", item);
    }
}

*/



