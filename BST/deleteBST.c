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
    if (root == NULL) return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

// Find minimum value node
struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Delete node from BST
struct node* deleteNode(struct node* root, int data) {
    if (root == NULL) return root;

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node with only right child or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        // Node with only left child
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get inorder successor
        struct node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
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
    char choice;
    int data;

    printf("BINARY SEARCH TREE OPERATIONS\n");
    while(1) {
        printf("\nChoose operation:\n");
        printf("[I]nsert | [D]elete | E[x]it\n");
        printf("Choice: ");
        scanf(" %c", &choice);

        switch(choice) {
            case 'i':
            case 'I':
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            
            case 'd':
            case 'D':
                printf("Enter data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;
            
            case 'x':
            case 'X':
                printf("Exiting program\n");
                exit(0);
            
            default:
                printf("Invalid choice!\n");
                continue;
        }

        printf("Current tree (in-order): ");
        inorder(root);
        printf("\n");
    }
    return 0;
}
