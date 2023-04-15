#include <stdio.h>
#include <stdlib.h>
#include "circularqueue.h"

/// @brief Initializes the queue to be used, sets proper values
/// @param q The queue to be initialized
void initQueue(CircularQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

/// @brief Enqueues a given value onto a given circular queue
/// @param q The queue to be changed
/// @param value The value to be placed in the queue
/// @return
int enqueue(CircularQueue *q, int value)
{
    if (isFull(q))
    {
        return -1;
    }

    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % BUFFER_SIZE;
    q->size++;
    return 0;
}

/// @brief Dequeues the next item and returns it.
/// @param q The queue to remove an item from
/// @return The item removed from the queue.
int dequeue(CircularQueue *q)
{
    if (isEmpty(q))
    {
        return -1;
    }

    int value = q->data[q->front];

    q->front = (q->front + 1) % BUFFER_SIZE;

    q->size--;

    return value;
}

/// @brief Returns, but does not remove, from the circular queue.
/// @param q The queue to peek from
/// @return The item at the front of the queue that was NOT removed.
int peek(CircularQueue *q)
{
    return q->data[q->front];
}

/// @brief Returns an int whether or not the queue is empty
/// @param q The queue to check
/// @return 1 if the queue is empty, 0 if otherwise.
int isEmpty(CircularQueue *q)
{
    return q->size == 0;
}

/// @brief Returns an int whether or not the queue is full
/// @param q The queue to check
/// @return 1 if the queue is full, 0 if otherwise.
int isFull(CircularQueue *q)
{
    return q->size == BUFFER_SIZE;
}

/// @brief Generates a formatted list to be printed.
/// @param q The queue to read.
void printAll(CircularQueue *q)
{
    printf("{");
    int i, count;
    for (i = q->front, count = 0; count < q->size; count++)
    {
        printf("%d", q->data[i]);
        i = (i + 1) % BUFFER_SIZE;
        if (count != q->size - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}
