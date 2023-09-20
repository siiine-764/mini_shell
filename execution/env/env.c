/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:57:27 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/20 22:41:08 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

//-fsanitize=address

struct Node* createNode(char  *val, char  *key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->key = key;

    // printf("----> val %s\n",  newNode->val);
    // printf("---> key %s\n",  newNode->key);
    newNode->next = NULL;
    return newNode;
}

void insertNode(struct Node** head, char  *val, char  *key) {
    struct Node* newNode = createNode(val, key);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        // printf("%s%s \n", newNode->key, newNode->val);
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        // newNode->next = NULL;
    }
}

void displayList(struct Node* head) {
    printf("%s\n",head->key);
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->key[0] && temp->val[0])
        {
            printf("%s", temp->key);
            printf("%s\n", temp->val);
        }
        temp = temp->next;
    }
    // printf("\n");
}

void displayList_export(struct Node* head)
{
    printf("%s\n",head->key);
    struct Node* temp = head;
    while (temp != NULL) {
            printf("declare -x %s", temp->key);
            printf("%s\n", temp->val);
        temp = temp->next;
    }
    // printf("\n");
}

void    get_path(char *path, t_path *p)
{
    int i;
    i = 0;

    p->path = ft_split(path, ':');

    while (p->path[i])
    {
        p->cnt++;
        // printf("*** %s ***\n", p->path[i]);
        i++;
    }
}
