#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ELEMENTS 100
#define ROW_SIZE 5

// Define the linked list node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* create_node(int value) 
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// Append a node to the end of the list
void append(Node** head, int value) 
{
    Node* new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) 
        temp = temp->next; // Traverse to the end
    temp->next = new_node;
}

// Bubble sort on linked list
void bubble_sort(Node* head) 
{
    if (head == NULL) return;

    int swapped;
    Node *ptr1;
    Node *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) 
        {
            if (ptr1->data > ptr1->next->data) {
                // Swap values
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1; // last element is now sorted
    } while (swapped); // Repeat until no swaps are made
}

// Print list in rows of ROW_SIZE
void print_list(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != NULL)  
    {
        printf("%4d ", temp->data);
        count++;
        if (count % ROW_SIZE == 0) printf("\n"); // New line after ROW_SIZE elements
        temp = temp->next;
    }
    if (count % ROW_SIZE != 0) printf("\n");
}

// Free list memory
void free_list(Node* head) {
    Node* temp;
    while (head != NULL) 
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    Node* head = NULL; // Initialize the linked list

    // Generate 100 random integers and store in list
    for (int i = 0; i < NUM_ELEMENTS; i++) 
    {
        int value = rand() % 1000; // random integer 0-999
        append(&head, value);
    }

    printf("Original list:\n");
    print_list(head);

    // Sort the list
    bubble_sort(head);

    printf("\nSorted list:\n");
    print_list(head);

    free_list(head);
    return 0;
}
