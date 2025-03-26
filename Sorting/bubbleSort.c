#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n, int* comparisons) {
    int temp;
    *comparisons = 0; // Initialize comparison count

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparisons)++; // Increment comparison count
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Start time measurement
    clock_t start_time = clock();

    int comparisons;
    bubbleSort(arr, n, &comparisons);

    // End time measurement
    clock_t end_time = clock();
    
    // Calculate time taken
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Sorted numbers in ascending order:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    printf("\nNumber of comparisons made: %d\n", comparisons);
    printf("Time taken for sorting: %.6f seconds\n", time_taken);

    free(arr); // Free allocated memory
    return 0;
}
