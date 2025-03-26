#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

// Create new node
struct node* newNode(int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert node according to BST rules
struct node* insert(struct node* root, int data) {
    if (root == NULL) {
        return newNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// In-order traversal (left-root-right)
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    struct node* root = NULL;
    int data;
    char choice;

    printf("BINARY SEARCH TREE CREATION\n");
    do {
        printf("Enter data to insert: ");
        scanf("%d", &data);
        root = insert(root, data);
        
        printf("Current tree (in-order): ");
        inorder(root);
        printf("\nContinue insertion? (y/n): ");
        scanf(" %c", &choice);  // Space before %c to handle newline
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
