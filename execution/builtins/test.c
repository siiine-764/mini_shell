#include <stdio.h>
#include <stdlib.h>

// Structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to delete a node from the linked list
void deleteNode(struct Node** head_ref, int key) {
    // Store the head node
    struct Node* temp = *head_ref;
    struct Node* prev = NULL;

    // If the head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next; // Changed head
        free(temp); // Free the old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If the key was not present in the linked list
    if (temp == NULL)
        return;

    // Unlink the node from the linked list
    prev->next = temp->next;
    free(temp); // Free the memory

    return;
}

// Function to print the linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Test the implementation
int main() {
    // Create the linked list: 1 -> 2 -> 3 -> 4 -> 5
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;
    struct Node* fourth = NULL;
    struct Node* fifth = NULL;

    // Allocate memory for the nodes
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));
    fourth = (struct Node*)malloc(sizeof(struct Node));
    fifth = (struct Node*)malloc(sizeof(struct Node));

    // Assign data values and set the next pointers
    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = fourth;

    fourth->data = 4;
    fourth->next = fifth;

    fifth->data = 5;
    fifth->next = NULL;

    printf("Original Linked List: ");
    printList(head);

    // Delete a node with value 3
    deleteNode(&head, 3);

    printf("Linked List after deletion: ");
    printList(head);

    // Free the memory allocated for the nodes
    free(head);
    free(second);
    free(third);
    free(fourth);
    free(fifth);

    return 0;
}