#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 200        // Number of elements in the list
#define MAX_VALUE 50 // Maximum random value (0-49)

// Doubly linked list node structure
typedef struct Node {
    int data;           // Integer data
    struct Node* prev;  // Pointer to previous node
    struct Node* next;  // Pointer to next node
} Node;

// Create a new node with given value
Node* createNode(int value) 
{
    Node* newNode = (Node*)malloc(sizeof(Node)); // Allocate memory
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Append a new node at the end of the list
void append(Node** head, int value) 
{
    Node* newNode = createNode(value);
    if (*head == NULL) // If list is empty, new node becomes head
    {       
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) // Traverse to the last node
        temp = temp->next;
    temp->next = newNode;      // Link new node at the end
    newNode->prev = temp;      // Set backward link
}

// Print the list (10 elements per row for readability)
void printList(Node* head) 
{
    int count = 0;
    Node* temp = head;
    while (temp != NULL) 
    {
        printf("%2d ", temp->data);
        if (++count % 10 == 0) 
            printf("\n"); // New line after 10 elements
        temp = temp->next;
    }
    printf("\n");
}

// Remove all duplicate values from the list
void removeDuplicates(Node* head) 
{
    for (Node* current = head; current != NULL; current = current->next) 
    {
        Node* runner = current->next; // Check all following nodes
        while (runner != NULL) 
        {
            if (runner->data == current->data) 
            {
                // Duplicate found; remove it
                Node* toDelete = runner;
                runner = runner->next; // Move runner forward before deletion

                // Update links of neighboring nodes
                if (toDelete->prev) toDelete->prev->next = toDelete->next;
                if (toDelete->next) toDelete->next->prev = toDelete->prev;

                free(toDelete); // Free memory of removed node
            } 
            else 
            {
                runner = runner->next; // Move to next node
            }
        }
    }
}

// Free all nodes in the list to avoid memory leaks
void freeList(Node* head) 
{
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/*
 * Program: Remove duplicates from a doubly linked list
 * Author: [Walid Krati]
 * Purpose: Generate 200 random integers in [0,49],
 *          store them in a doubly linked list, remove duplicates,
 *          and display the list before and after removal.
 */
int main() 
{
    srand(time(NULL)); // Seed random number generator
    Node* list = NULL;

    // Generate 200 random integers and append to the list
    for (int i = 0; i < N; i++)
        append(&list, rand() % MAX_VALUE);

    printf("Original list:\n");
    printList(list); // Display initial list

    removeDuplicates(list); // Remove duplicate elements

    printf("\nList after removing duplicates:\n");
    printList(list); // Display final list

    freeList(list); // Free allocated memory
    return 0;
}
