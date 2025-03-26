#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct MaxHeap {
    int size;
    int arr[MAX_SIZE];
};

// Function prototypes
void insert(struct MaxHeap* heap, int value);
void removeRoot(struct MaxHeap* heap);
void heapify(struct MaxHeap* heap, int index);
void displayHeap(struct MaxHeap* heap);
int parent(int index);
int leftChild(int index);
int rightChild(int index);

int main() {
    struct MaxHeap heap;
    heap.size = 0;

    // Insert data in specified order
    int values[] = {5, 7, 3, 10, 14, 12, 2, 13, 20, 9};
    printf("Inserting values into max-heap: ");
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        insert(&heap, values[i]);
        printf("%d ", values[i]);
    }
    printf("\n");

    // Display initial heap
    printf("Max-Heap after insertion: ");
    displayHeap(&heap);

    // Perform three root removals
    for (int i = 0; i < 3; i++) {
        removeRoot(&heap);
        printf("Max-Heap after removing root: ");
        displayHeap(&heap);
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

    // Store the root value to be removed
    int rootValue = heap->arr[0];
    
    // Replace root with the last element
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    // Heapify down from the root
    heapify(heap, 0);

    printf("Removed root element: %d\n", rootValue);
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
    printf("\n");
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
