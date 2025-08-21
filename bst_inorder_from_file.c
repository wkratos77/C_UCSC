/*
 * Program: Read integers from a file and store them in a binary tree
 * Author: [Walid Krati]
 * Date: [21/08/2025]
 *
 * Description:
 *  - Reads the first integer as the number of values (n)
 *  - Reads n integers and inserts them into a binary search tree
 *  - Prints the values in sorted order using inorder traversal
 */
#include <stdio.h>
#include <stdlib.h>

// Define a binary tree node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new tree node
Node* createNode(int value) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) 
    {
        perror("Memory allocation failed");
        exit(1);
    }
    newNode->data = value; // Set the data
    newNode->left = newNode->right = NULL; // Initialize left and right children to NULL
    return newNode;
}

// Insert a value into the binary search tree
Node* insert(Node* root, int value) {
    if (root == NULL) 
        return createNode(value); // Create a new node if the tree is empty

    if (value < root->data) // Insert in the left subtree
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

// Inorder traversal of the tree
void inorder(Node* root) 
{
    if (root == NULL) // Base case: if the node is NULL, return
        return;
    inorder(root->left); // Traverse the left subtree
    printf("%d ", root->data); // Print the current node's data
    inorder(root->right); // Traverse the right subtree
}

// Free all nodes of the tree
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() 
{
    FILE* infile = fopen("input.txt", "r"); // Open the input file for reading
    if (!infile) 
    {
        perror("Error opening input file");
        return 1;
    }

    int n;
    if (fscanf(infile, "%d", &n) != 1 || n <= 0) // Read the number of integers
    {
        printf("Invalid number of integers\n");
        fclose(infile);
        return 1;
    }

    int value;
    Node* root = NULL;

    // Read n integers and insert into the binary tree
    for (int i = 0; i < n; i++) 
    {
        if (fscanf(infile, "%d", &value) != 1) // Read each integer
        {
            printf("Error reading value %d\n", i + 1);
            fclose(infile);
            freeTree(root);
            return 1;
        }
        root = insert(root, value); // Insert the value into the binary search tree
    }

    fclose(infile);

    // Print values inorder (sorted)
    printf("Inorder traversal of the tree:\n");
    inorder(root);
    printf("\n");

    // Clean up memory
    freeTree(root);

    return 0;
}
