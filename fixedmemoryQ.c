#include <stdio.h>
#include <stdlib.h>

// Define Max size with a macro
#define MAXSIZE 100
// Define a structure called "Queue"
struct queue{
    int items[MAXSIZE];
    int rear , front;
};

//Intialise a Queue
struct queue q , *pq;
void initialise()
{
    pq = &q;
    q.front = 0;
    q.rear = -1;
}
// Function to check if the QUEUE is full
int full()
{
    return q.rear == MAXSIZE -1;
}
// Function to check if the QUEUE is empty
int empty()
{
    return q.front > q.rear;
}
// Function to insert an element onto the Queue
void insert(int v)
{
    if(full())
    {
        printf("Overflow !");
    }
    else
    {
        q.rear++;
        pq -> items[q.rear] = v;
    }
    return;
}
// Function to delete an element from the Queue
int deleteQ()
{
    if(empty())
    {
        printf(" Queue is empty !");
    }
    else
    {
        return pq -> items[q.front++];
    }
}

// Function to display the content of the stack
void display()
{
    if(empty())
    {
        printf("Queue is empty !");
    }
    else
    {
        printf("\nQueue: ");
        for(int i = q.front; i <= q.rear; i++)
        {
            printf("%d ", pq -> items[i]);
        }
    }
    printf("\n");
  return;
}
int main() {
  int i, choice, value, testCases;
  scanf("%d", &testCases);
  for (i = 0; i < testCases; ++i) {
    printf("#############################\n\t\tTEST CASE "
          "%d\t\n#############################\n",
          i + 1);
    initialise();
    do {
      printf("\nMenu:\n");
      printf("1. Insert\n");
      printf("2. Delete\n");
      printf("3. Display\n");
      printf("4. Exit\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);
      //printf("%d", choice);
      switch (choice) {
      case 1:
        printf("\nEnter the value to push: ");
        scanf("%d", &value);
        insert( value);
        display();
        break;
      case 2:
        value = deleteQ();
          printf("\nDeleted element: %d\n", value);
        display();
        break;
      case 3:
        display();
        break;
      case 4:
        printf("\nExiting the program.\n");
        break;
      default:
        printf("\nInvalid choice. Please enter a valid option.\n");
      }
    } while (choice != 4);
  }
  return 0;
}
