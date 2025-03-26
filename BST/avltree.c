#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int height;
};

// Function prototypes
int height(struct TreeNode* node);
int max(int a, int b);
int getBalance(struct TreeNode* node);
struct TreeNode* createNode(int key);
struct TreeNode* rightRotate(struct TreeNode* y);
struct TreeNode* leftRotate(struct TreeNode* x);
struct TreeNode* insert(struct TreeNode* node, int key);
void printBalanceFactors(struct TreeNode* root);

int main() {
    struct TreeNode* root = NULL;
    int initial_values[] = {8, 6, 4, 3, 7, 5, 10, 11, 9};
    int insert_value = 2;

    // Part a: Create initial tree and show balance factors
    printf("Creating initial AVL tree with values: ");
    for(int i = 0; i < sizeof(initial_values) / sizeof(initial_values[0]); i++) {
        root = insert(root, initial_values[i]);
        printf("%d ", initial_values[i]);
    }
    
    printf("\n\nBalance factors after initial insertion:\n");
    printBalanceFactors(root);

    // Part b: Insert 2 and check balance
    root = insert(root, insert_value);
    printf("\nAfter inserting %d:\n", insert_value);
    printBalanceFactors(root);

    return 0;
}

int height(struct TreeNode* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(struct TreeNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

struct TreeNode* createNode(int key) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is initially added at leaf
    return node;
}

struct TreeNode* rightRotate(struct TreeNode* y) {
    struct TreeNode* x = y->left;
    struct TreeNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

struct TreeNode* leftRotate(struct TreeNode* x) {
    struct TreeNode* y = x->right;
    struct TreeNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

struct TreeNode* insert(struct TreeNode* node, int key) {
    // Perform the normal BST insertion
    if (!node) return createNode(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    
	// Update the height of this ancestor node
	node->height = 1 + max(height(node->left), height(node->right));

	// Check the balance factor to see if this node became unbalanced
	int balance = getBalance(node);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (balance > 1 && key < node->left->data)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && key > node->right->data)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && key > node->left->data) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && key < node->right->data) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node; // return the (unchanged) node pointer
}

void printBalanceFactors(struct TreeNode* root) {
	if (root) {
		printBalanceFactors(root->left);
		printf("Node %2d: Balance Factor = %2d\n", root->data, getBalance(root));
		printBalanceFactors(root->right);
	}
}
