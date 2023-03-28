#include <stdio.h>
#include <stdlib.h>
#include "circularqueue.h"

void initQueue(CircularQueue *q){
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

int enqueue(CircularQueue *q, int value){
    if(isFull(q)){
        return -1;
    }
    
    q->data[q->rear] = value;
    q->rear = (q->rear+1) % BUFFER_SIZE;
    q->size++;
    return 0;
}

int dequeue(CircularQueue *q){
    if(isEmpty(q)){
        return -1;
    }

    int value = q->data[q->front];

    q->front = (q->front + 1) % BUFFER_SIZE;
    
    q->size--;

    return value;
}

int peek(CircularQueue *q){
    return q->data[q->front];
}

int isEmpty(CircularQueue *q){
    return q->size == 0;
}

int isFull(CircularQueue *q){
    return q->size == BUFFER_SIZE;
}

void printAll(CircularQueue *q){
    printf("{");
    int i, count;
    for(i = q->front, count = 0; count < q->size; count++){
        printf("%d", q->data[i]);
        i = (i + 1) % BUFFER_SIZE;
        if(count != q->size-1){
            printf(", ");
        }
    }
    printf("}\n");
}


