// Program 3: Circular Queue (Fixed Memory) - Menu Driven

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5 // Maximum number of elements in the queue

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

void initializeQueue(CircularQueue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isFull(CircularQueue* queue) {
    if ((queue->rear + 1) % MAX_SIZE == queue->front) {
        return 1;
    }
    return 0;
}

int isEmpty(CircularQueue* queue) {
    if (queue->front == -1) {
        return 1;
    }
    return 0;
}

void enqueue(CircularQueue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue Overflow!\n");
        return;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->items[queue->rear] = value;
    printf("Enqueued: %d\n", value);
}

int dequeue(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue Underflow!\n");
        return -1; // Indicate error
    }

    int value = queue->items[queue->front];

    if (queue->front == queue->rear) {
        initializeQueue(queue); // Reset the queue
    } else {
        queue->front = (queue->front + 1) % MAX_SIZE;
    }
    printf("Dequeued: %d\n", value);
    return value;
}

void displayQueue(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue: ");
    int i = queue->front;
    do {
        printf("%d ", queue->items[i]);
        i = (i + 1) % MAX_SIZE;
    } while (i != (queue->rear + 1) % MAX_SIZE);
    printf("\n");
}

int main() {
    CircularQueue queue;
    initializeQueue(&queue);
    int choice, value;

    while (1) {
        printf("\n******Menu*******:\n");
        printf("_____________________\n\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&queue, value);
                displayQueue(&queue);
                break;
            case 2:
                dequeue(&queue);
                displayQueue(&queue);
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}