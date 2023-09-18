/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 00:58:19 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/18 20:48:07 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

// Function to delete a node from the linked list based on a string key
void deleteNode(struct Node** head_ref, const char* key)
{
    // Store the head node
    struct Node* temp = *head_ref;
    struct Node* prev = NULL;

    // If the head node itself holds the key to be deleted
    if (temp != NULL && strcmp(temp->key, key) == 0) {
        *head_ref = temp->next; // Changed head
        free(temp); // Free the old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && strcmp(temp->key, key) != 0) {
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

void    un_set(struct Node *head, char *add_key)
{
    struct Node *temp = head;
    int bl = 0;

    if (!add_key[0])
    {
        printf("unset: not enough arguments");
        exit(1);
    }

    while (temp != NULL)
    {
        if(strcmp(temp->key, add_key) == 0)
        {
            bl = 1;
            deleteNode(&head, add_key);
        }
        temp = temp->next;
    }
    if (bl == 0)
        printf("not find this key\n");
}
