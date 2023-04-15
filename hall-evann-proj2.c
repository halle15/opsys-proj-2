#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "circularqueue.h"

// CONSTANTS
#define THREAD_ITERATIONS 1000
#define PRODUCER_DELAY 100000
#define CONSUMER_DELAY 105000
#define RANDOMSLEEP_UPPERBOUND 10000
#define RANDOMITEM_UPPERBOUND 100

// FUNCTION PROTOTYPES
void *producer(void *param);
void *consumer(void *param);
int rnd(int bound);
void seedRandom();

// GLOBAL VARIABLES
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fullBuffer = PTHREAD_COND_INITIALIZER;
pthread_cond_t emptyBuffer = PTHREAD_COND_INITIALIZER;
pthread_barrier_t barrier;

CircularQueue q;
//-------------------------------

/// @brief A small modification of the random number generation function.
/// @param bound The upper bound of the number to be randomly generated
/// @return The random number between 0 and the bound
int rnd(int bound)
{
    return rand() % bound;
}

/// @brief Performs a bitwise XOR against the threadID to provide a pseudorandom seed.
void seedRandom()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    srand(now.tv_nsec ^ pthread_self());
}

int main(int argc, char *argv[])
{
    // sets queue object to starting parameters
    initQueue(&q);

    // creating a barrier object to force the threads to not start until all have begun
    pthread_barrier_init(&barrier, NULL, 2);

    // creates the threads, passes in the consumer or producer function to be ran, as well as the global queue object.
    pthread_t tid_1, tid_2;
    if (pthread_create(&tid_1, NULL, producer, &q) != 0 || pthread_create(&tid_2, NULL, consumer, &q) != 0)
    {
        perror("Failed to create threads");
        return 1;
    }

    // when threads have completed, join them together with relevant params (if not null) and finish execution of program.
    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);

    // destroy mutex lock.
    pthread_mutex_destroy(&mutex);
    // destroy cond signals
    pthread_cond_destroy(&emptyBuffer);
    pthread_cond_destroy(&fullBuffer);
    // destroy original barrier obj
    pthread_barrier_destroy(&barrier);

    printf("Program Complete!\n");

    return 0;
}

/// @brief The function that represents the producer in the problem. Randomly generates numbers and places them in the Queue.
/// @param param The global queue being passed in.
/// @return No output, but fills global queue.
void *producer(void *param)
{
    seedRandom(); // this is called before the barrier to ensure there is a slight difference in recorded time

    pthread_barrier_wait(&barrier); // this is a call to wait for the signal from the barrier to continue

    int item; // declare item

    for (int a = 0; a < THREAD_ITERATIONS; a++)
    {
        // Generate a random number
        item = rnd(RANDOMITEM_UPPERBOUND);

        pthread_mutex_lock(&mutex); // this is a call to wait for the signal from the barrier to continue

        // if the buffer is full, the thread waits for the signal from a consumer to ensure that it doesn't overplace.
        if (isFull(&q))
        {
            pthread_cond_wait(&fullBuffer, &mutex);
        }

        if (enqueue(&q, item))
        {
            printf("Failed to put!\n"); // THIS SHOULD NOT BE REACHED!
            pthread_exit(NULL);
        }
        else
        {
            printf("producer produced %d\n", item); // Success
        }

        pthread_cond_signal(&emptyBuffer); // signal to consumer threads that it has been added to
        pthread_mutex_unlock(&mutex);      // allow other threads to access critical resource.

        printAll(&q);
        usleep(PRODUCER_DELAY + rnd(RANDOMSLEEP_UPPERBOUND)); // randomly calculated delay. Base time is calculated by RND, then added to with the modifier.
    }
}

/// @brief The function that represents the consumer in the problem. Randomly eats numbers.
/// @param param The global queue being passed in.
/// @return No output, but eats from global queue.
void *consumer(void *param)
{
    seedRandom(); // this is called before the barrier to ensure there is a slight difference in recorded time

    pthread_barrier_wait(&barrier); // barrier to ensure they begin at similar times.

    int item; // declare item

    for (int a = 0; a < THREAD_ITERATIONS; a++)
    {
        pthread_mutex_lock(&mutex);

        // ensure that if the queue is empty, wait for a producer thread to signal.
        if (isEmpty(&q))
        {
            pthread_cond_wait(&emptyBuffer, &mutex);
        }

        item = dequeue(&q);

        if (item == -1)
        {
            printf("Failed to consume!\n"); // SHOULD NOT bE REACHED!
            pthread_exit(NULL);
        }
        else
        {
            printf("consumer consumed %d\n", item);
        }

        pthread_cond_signal(&fullBuffer); // signal to producer threads that the last item was eaten.
        pthread_mutex_unlock(&mutex);

        printAll(&q);
        usleep(CONSUMER_DELAY + rnd(RANDOMSLEEP_UPPERBOUND)); // randomly calculated delay. Base time is calculated by RND, then added to with the modifier.
    }
}
