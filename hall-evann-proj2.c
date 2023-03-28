#include <stdlib.h> // Required for rand()
#include <stdio.h>
#include "circularqueue.h"
#include <pthread.h>

void *producer(void *param);
void *consumer(void *param);

CircularQueue q;

int main(int argc, char *argv[]) {
    pthread_t thr_1, thr_2;

    pthread_attr_t attr_1, attr_2;
    pthread_t tid_1, tid2;

    pthread_attr_init(&attr_1);
    pthread_attr_init(&attr_2);

    pthread_create(&tid_1, &attr_1, producer, &q);
    pthread_create(&thr_2, &attr_2, consumer, &q);

    pthread_join(thr_1, NULL);
    pthread_join(thr_2, NULL);
   
    
    // Initialize any required variables and the buffer

    // Create the producer and consumer threads using pthread_create()

    // Join the threads using pthread_join()

    return 0;
}


void *producer(void *param) {
    int item;

    while (1) {
        // Sleep for a random period of time
        sleep(3);

        // Generate a random number
        item = rand();

        if (enqueue(&q, item))
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

        if (dequeue(&q) )
            printf("g");
            //fprintf("report error condition");
        else
            printf("consumer consumed %d\n", item);
    }
}




