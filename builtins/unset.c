/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 00:58:19 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/25 19:52:07 by mayache-         ###   ########.fr       */
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
    if (temp != NULL && strcmp(temp->key, key) == 0)
    {
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
    // free(temp); // Free the memory

    return;
}

void    un_set(struct Node *head, char *add_key)
{
    struct Node *temp = head;
    char *str_join;
    
    while (temp != NULL)
    {
        str_join = ft_strjoin(add_key, "=");
        // printf("temp->key : %s, add key : %s\n",temp->key, str_join);
        if(strcmp(temp->key, str_join) == 0)
        {
            deleteNode(&head, str_join);
        }
        temp = temp->next;
    }
}
