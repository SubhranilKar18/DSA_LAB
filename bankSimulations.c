#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TELLERS 4
#define NUM_TRANSACTION_TYPES 4

typedef struct Customer {
    int arrivalTime;
    int transactionDuration;
    int startTime;
    int endTime;
    struct Customer* next;
} Customer;

typedef struct Queue {
    Customer* front;
    Customer* rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, int arrivalTime, int duration) {
    Customer* customer = (Customer*)malloc(sizeof(Customer));
    customer->arrivalTime = arrivalTime;
    customer->transactionDuration = duration;
    customer->startTime = -1;
    customer->endTime = -1;
    customer->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = customer;
        return;
    }

    queue->rear->next = customer;
    queue->rear = customer;
}

Customer* dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }

    Customer* customer = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return customer;
}

void printQueue(Queue* queue, int queueNumber) {
    printf("Queue %d: ", queueNumber);
    Customer* current = queue->front;
    if (current == NULL) {
        printf("Empty\n");
        return;
    }

    while (current != NULL) {
        printf("(Arr:%d, Dur:%d) -> ", current->arrivalTime, current->transactionDuration);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    int numCustomers;
    int transactionDurations[NUM_TRANSACTION_TYPES];
    Queue* queues[NUM_TELLERS];
    Customer* tellers[NUM_TELLERS];
    int currentTime = 0;
    int totalWaitingTime = 0;
    int servedCustomers = 0;

    // Vary Parameters
    numCustomers = 20; // We are taking it as example 20 customers
    transactionDurations[0] = 2; // let the  durations be these
    transactionDurations[1] = 3;
    transactionDurations[2] = 4;
    transactionDurations[3] = 5;

    // Initialize queues and tellers
    for (int i = 0; i < NUM_TELLERS; i++) {
        queues[i] = createQueue();
        tellers[i] = NULL;
    }

    // Generate customers and enqueue them
    srand(time(NULL));
    for (int i = 0; i < numCustomers; i++) {
        int arrivalTime = rand() % 30; // Random arrival time up to 30 seconds
        int transactionType = rand() % NUM_TRANSACTION_TYPES;
        int duration = transactionDurations[transactionType];

        int shortestQueue = 0;
        for(int j = 1; j < NUM_TELLERS; j++){
            int queue1size = 0;
            int queue2size = 0;
            Customer* temp1 = queues[shortestQueue]->front;
            Customer* temp2 = queues[j]->front;

            while(temp1 != NULL){
                queue1size++;
                temp1 = temp1->next;
            }
            while(temp2 != NULL){
                queue2size++;
                temp2 = temp2->next;
            }

            if(queue2size < queue1size){
                shortestQueue = j;
            }
        }
        enqueue(queues[shortestQueue], arrivalTime, duration);
    }

    // Simulation loop
    while (1) {
        int allQueuesEmpty = 1;
        for (int i = 0; i < NUM_TELLERS; i++) {
            if (queues[i]->front != NULL || tellers[i] != NULL) {
                allQueuesEmpty = 0;
                break;
            }
        }

        if (allQueuesEmpty && servedCustomers == numCustomers) {
            break;
        }

        for (int i = 0; i < NUM_TELLERS; i++) {
            // Check if teller is free
            if (tellers[i] == NULL) {
                // Get customer from queue
                Customer* customer = dequeue(queues[i]);
                if (customer != NULL) {
                    tellers[i] = customer;
                    tellers[i]->startTime = currentTime;
                    tellers[i]->endTime = currentTime + tellers[i]->transactionDuration;
                }
            }

            // Check if teller finished processing
            if (tellers[i] != NULL && tellers[i]->endTime == currentTime) {
                totalWaitingTime += tellers[i]->startTime - tellers[i]->arrivalTime;
                servedCustomers++;
                free(tellers[i]);
                tellers[i] = NULL;
            }
        }

        // Print queue contents
        for (int i = 0; i < NUM_TELLERS; i++) {
            printQueue(queues[i], i + 1);
        }
        printf("Current Time: %d\n", currentTime);
        printf("----------------------\n");

        currentTime++;
    }

    // Calculate and print average waiting time
    if (servedCustomers > 0) {
        double averageWaitingTime = (double)totalWaitingTime / servedCustomers;
        printf("Average Waiting Time: %.2f seconds\n", averageWaitingTime);
    } else {
        printf("No customers served.\n");
    }

    // Free allocated memory (queues)
    for(int i = 0; i < NUM_TELLERS; i++){
        Customer* current = queues[i]->front;
        while(current != NULL){
            Customer* temp = current;
            current = current->next;
            free(temp);
        }
        free(queues[i]);
    }

    return 0;
}