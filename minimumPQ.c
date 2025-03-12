#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int priority;
    char data[50];
} Element;

typedef struct {
    Element heap[MAX_SIZE];
    int size;
} PriorityQueue;

void swap(Element *a, Element *b) {
    Element temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(PriorityQueue *pq, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && pq->heap[index].priority < pq->heap[parent].priority) {
        swap(&pq->heap[index], &pq->heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void heapify_down(PriorityQueue *pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->heap[left].priority < pq->heap[smallest].priority) {
        smallest = left;
    }

    if (right < pq->size && pq->heap[right].priority < pq->heap[smallest].priority) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&pq->heap[index], &pq->heap[smallest]);
        heapify_down(pq, smallest);
    }
}

void insert(PriorityQueue *pq, int priority, char *data) {
    if (pq->size >= MAX_SIZE) {
        printf("Priority queue is full.\n");
        return;
    }

    pq->heap[pq->size].priority = priority;
    strcpy(pq->heap[pq->size].data, data);
    pq->size++;
    heapify_up(pq, pq->size - 1);
}

Element pop(PriorityQueue *pq) {
    Element result = {-1, ""}; // Initialize with invalid values
    if (pq->size <= 0) {
        printf("Priority queue is empty.\n");
        return result;
    }

    result = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    heapify_down(pq, 0);
    return result;
}

void display(PriorityQueue *pq) {
    printf("Priority Queue:\n");
    for (int i = 0; i < pq->size; i++) {
        printf("(Priority: %d, Data: %s)\n", pq->heap[i].priority, pq->heap[i].data);
    }
    printf("\n");
}

int main() {
    PriorityQueue pq = {{}, 0};
    int choice, priority;
    char data[50];
    Element popped;

    while (1) {
        printf("1. Insert\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter priority: ");
                scanf("%d", &priority);
                printf("Enter data: ");
                scanf(" %49[^\n]", data); // Read up to 49 characters, including spaces.
                insert(&pq, priority, data);
                break;
            case 2:
                popped = pop(&pq);
                if (popped.priority != -1) {
                    printf("Popped: (Priority: %d, Data: %s)\n", popped.priority, popped.data);
                }
                break;
            case 3:
                display(&pq);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}