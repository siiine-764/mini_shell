/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:57:27 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/18 22:04:50 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

//-fsanitize=address

// void    add_env(t_env   *e, char *env)
// {
//     e->test++;
//     char    **dd = malloc(sizeof(char *) * e->test + 1);
//     dd = ft_arr_dup(g_env);
//     free(g_env);
//     int i = 0;
//     while(i < e->test)
//     {
//         dd[i] = str_join(key, value);
//         i++;
//     }
//     // e->value[e->test] = value;
//     // e->key[e->test] = key;
// }


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
        // printf("------ddddd------");
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
            printf("%s", temp->key);
            printf("%s\n", temp->val);
        temp = temp->next;
    }
    // printf("\n");
}

// void    ft_find_replace(struct Node* head, char *add_key, char *add_val)
// {
//     struct Node* temp = head;
//     // int bl = 0;
//     // if (!add_key || !add_val)
//     //     return ;
//     // printf("|||||||||||\n");
//     // printf("|addkey %s|\n", add_key);
//     // printf("|||||||||||\n");
//     while (temp != NULL)
//     {
//         // printf("|||||||||||\n");
//         // printf("|addkey %s|\n", temp->key);
//         // printf("|||||||||||\n");
//         if(strcmp(temp->key, add_key) == 0)
//         {
//             // bl = 1;
//             add_key = str_join(add_key, "=");
//             insertNode(&head, add_val, add_key);
//             // printf("yassine is here\n");
//             // strcpy(temp->val, add_val);
//         }
//         // printf("%s...... \n", temp-)
//         // printf("%s.....", temp->key);
//         // printf("%s...... \n", temp->val);
//         // if(bl != 1)
//         // {
//         // }
//         temp = temp->next;
//     }
// }


int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    struct Node* head = NULL;
    // (void)env;
    //     char *str;
    // while (1)
    // {
    //     readline(str);
    // }
    // printf("%s\n", str);
    // exit(1);
    // execute();
    // printf("dddd");
    t_env   *e = malloc(sizeof(t_env));
    
    create_env(env, &head);
    // displayList(head);

    printf("*********************************\n");
    displayList(head);
    ft_ex_port(head, "fffff",  "ssssssss");
    printf("+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-\n");
    displayList(head);
    un_set(head, "fffff=");
    // un_set(head, "USER=");

    // un_set(head, "TERM=");
        // displayList_export(head);
    
    printf("--------------------------------\n");
    displayList(head);

    // free(env);
    free(e);
    
    // free(e->key);
    // free(e->val);
    return 0;
}


