#include <stdlib.h> // Required for rand()
#include <stdio.h>
#include "circularqueue.h"
#include <pthread.h>

void *producer(void *param);
void *consumer(void *param);

CircularQueue q;

int rnd(int bound){
    return rand() % bound;
}

int main(int argc, char *argv[]) {

    printf("started\n");



    
    pthread_t thr_1, thr_2;

    pthread_attr_t attr_1, attr_2;
    pthread_t tid_1, tid_2;

    pthread_attr_init(&attr_1);
    pthread_attr_init(&attr_2);

    pthread_create(&tid_1, &attr_1, producer, &q);
    pthread_create(&tid_2, &attr_2, consumer, &q);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    
    
    
    // Initialize any required variables and the buffer

    // Create the producer and consumer threads using pthread_create()

    // Join the threads using pthread_join()

    return 0;
    
}


void *producer(void *param) {
    int item;

    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    srand(now.tv_nsec ^ pthread_self());

    printf("%i\n", pthread_self());


    while (1) {

        // Generate a random number
        item = rnd(50);

        if (enqueue(&q, item)){
            printf("Failed to put!\n");
        }
        else{
            printf("producer produced %d\n", item);
        }

        printAll(&q);
        usleep(250000 + rnd(100000));
    }
}

void *consumer(void *param) {
    int item;

    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    srand(now.tv_nsec ^ pthread_self());


    printf("%i\n", pthread_self());


    while (1) {

        item = dequeue(&q);

        if (item == -1){
            printf("Failed to consume!\n");
        }
        else{
            printf("consumer consumed %d\n", item);
        }

        printAll(&q);
        usleep(265000 + rnd(100000));
        }
}




