#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure for Max Heap
struct MaxHeap {
    int size;
    int arr[MAX_SIZE];
};

// Function prototypes for Max Heap
void insert(struct MaxHeap* heap, int value);
void removeRoot(struct MaxHeap* heap);
void heapify(struct MaxHeap* heap, int index);
void displayHeap(struct MaxHeap* heap);
int parent(int index);
int leftChild(int index);
int rightChild(int index);

// Structure for Max Priority Queue
struct MaxPriorityQueue {
    struct MaxHeap heap;
};

// Function prototypes for Max Priority Queue
void enqueue(struct MaxPriorityQueue* pq, int value);
int dequeue(struct MaxPriorityQueue* pq);
void displayPriorityQueue(struct MaxPriorityQueue* pq);

int main() {
    struct MaxPriorityQueue pq;
    pq.heap.size = 0;

    // Test data to insert into the priority queue
    int values[] = {5, 7, 3, 10, 14, 12, 2, 13, 20, 9};
    printf("Inserting values into max priority queue: ");
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        enqueue(&pq, values[i]);
        printf("%d ", values[i]);
    }
    printf("\n");

    // Display initial max priority queue
    printf("Max Priority Queue after insertion: ");
    displayPriorityQueue(&pq);

    // Extract max values while maintaining max heap
    printf("Extracting max values:\n");
    while (pq.heap.size > 0) {
        int maxValue = dequeue(&pq);
        printf("Extracted max value: %d\n", maxValue);
        displayPriorityQueue(&pq);
    }

    return 0;
}

// Function to insert a value into the max-heap
void insert(struct MaxHeap* heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }
    
    // Insert the new value at the end
    heap->arr[heap->size] = value;
    heap->size++;

    // Heapify up
    int index = heap->size - 1;
    while (index != 0 && heap->arr[parent(index)] < heap->arr[index]) {
        // Swap with parent
        int temp = heap->arr[parent(index)];
        heap->arr[parent(index)] = heap->arr[index];
        heap->arr[index] = temp;

        index = parent(index);
    }
}

// Function to remove the root element from the max-heap
void removeRoot(struct MaxHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty!\n");
        return;
    }

    // Replace root with the last element
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    // Heapify down from the root
    heapify(heap, 0);
}

// Function to maintain the max-heap property by heapifying down
void heapify(struct MaxHeap* heap, int index) {
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    // Check if left child exists and is greater than current largest
    if (left < heap->size && heap->arr[left] > heap->arr[largest]) {
        largest = left;
    }

    // Check if right child exists and is greater than current largest
    if (right < heap->size && heap->arr[right] > heap->arr[largest]) {
        largest = right;
    }

    // If largest is not the current index, swap and continue to heapify down
    if (largest != index) {
        int temp = heap->arr[index];
        heap->arr[index] = heap->arr[largest];
        heap->arr[largest] = temp;

        // Recursively call to continue to maintain the max-heap property
        heapify(heap, largest);
    }
}

// Function to display the elements of the max-heap
void displayHeap(struct MaxHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
}

// Helper functions to get parent and child indices
int parent(int index) {
    return (index - 1) / 2;
}

int leftChild(int index) {
    return (2 * index + 1);
}

int rightChild(int index) {
    return (2 * index + 2);
}

// Function to enqueue a value into the priority queue
void enqueue(struct MaxPriorityQueue* pq, int value) {
    insert(&pq->heap, value);
}

// Function to dequeue (extract max) from the priority queue
int dequeue(struct MaxPriorityQueue* pq) {
    if (pq->heap.size <= 0) {
        printf("Priority Queue is empty!\n");
        return -1; // Return -1 or some error code when empty
    }

    // Store root value to return later
    int rootValue = pq->heap.arr[0];

    // Remove root from max-heap
    removeRoot(&pq->heap);

    return rootValue; // Return extracted maximum value
}

// Function to display elements of the priority queue
void displayPriorityQueue(struct MaxPriorityQueue* pq) {
   displayHeap(&pq->heap);
   printf("\n");
}
