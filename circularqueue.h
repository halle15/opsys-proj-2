#define BUFFER_SIZE 5

typedef struct {
    int data[BUFFER_SIZE];
    int front;
    int rear;
    int size;
} CircularQueue;

void initQueue(CircularQueue *q);
int enqueue(CircularQueue *q, int value);
int dequeue(CircularQueue *q);
int peek(CircularQueue *q);
int isEmpty(CircularQueue *q);
int isFull(CircularQueue *q);
void printAll(CircularQueue *q);

