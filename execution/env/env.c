/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:57:27 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/26 17:08:57 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

//-fsanitize=address

struct Node* createNode(char  *val, char  *key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

void insertNode(struct Node** head, char  *val, char  *key)
{
    struct Node* newNode = createNode(val, key);

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct Node* temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void displayList(struct Node* head)
{
    printf("%s\n",head->key);
    struct Node* temp = head;
    while (temp != NULL)
    {
        if (temp->key[0] && temp->val[0])
        {
            temp->content = temp->key;
            temp->content = ft_strjoin(temp->content, temp->val);
            // printf("%s\n", temp->content);
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
    while (temp != NULL)
    {
            printf("declare -x %s", temp->key);
            printf("%s\n", temp->val);
        temp = temp->next;
    }
    // printf("\n");
}


void	create_env(char **env, struct Node** head)
{
	int		i;

	i = 0;
    while(env[i])
    {
        insertNode(head, get_value(env[i]), get_key(env[i]));
        i++;
    }
}