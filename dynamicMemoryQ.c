#include <stdio.h>
#include <stdlib.h>

// Create Node and Queue structures.
struct Node {
  int data;
  struct Node *next;
};

typedef struct Node *NODEPTR;
struct Queue {
  NODEPTR front, rear;
};
// Function to initialize the Queue
struct Queue q , *pq;
void initialize()
{
    pq = &q;
    q.front = q.rear = NULL;
}

// Function to check if the QUEUE is empty
int empty()
{
    return q.front == NULL;
}

// Function to insert an element onto the Queue
void insert(int v)
{
    NODEPTR temp = (NODEPTR)malloc(sizeof(struct Node));
    if(temp == NULL)
    {
        printf("Overflow !");
    }
    else
    {
        temp -> data = v;
        temp -> next = NULL;
        if(empty())
        {
            q.front = q.rear = temp;
        }
        else
        {
            q.rear -> next = temp;
            q.rear = temp;
        }
    }
    return;
}
// Function to delete an element from the Queue
void deleteQ()
{
    if(empty())
    {
        printf(" Queue is empty !");
    }
    else
    {
        NODEPTR temp = q.front;
        q.front = q.front -> next;
        free(temp);
    }
}
// Function to display the content of the Queue
void display()
{
    if(empty())
    {
        printf("Queue is empty !");
    }
    else
    {
        NODEPTR temp = q.front;
        printf("\nQueue: ");
        while(temp != NULL)
        {
            printf("%d ",temp -> data);
            temp = temp -> next;
        }
    }
}

// Function to free the dynamically allocated memory
void cleanup()
{
    NODEPTR temp;
    while(q.front != NULL)
    {
        temp = q.front;
        q.front = q.front -> next;
        free(temp);
    }
}


int main() {
  
  int i, choice, value, testCases;

  scanf("%d", &testCases);
  for (i = 0; i < testCases; ++i) {
    printf("#############################\n\t\tTEST CASE "
           "%d\t\n#############################\n",
           i + 1);

    initialize();

    do {
      printf("\nMenu:\n");
      printf("1. Insert\n");
      printf("2. Delete\n");
      printf("3. Display\n");
      printf("4. Exit\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);

      switch (choice) {
      case 1:
        printf("\nEnter the value to push: ");
        scanf("%d", &value);
        insert(value);
        display();
        break;
      case 2:
           deleteQ();
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

    // Free the dynamically allocated memory
    cleanup();
  }

  return 0;
}
