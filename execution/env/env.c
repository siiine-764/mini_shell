/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:57:27 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/18 18:56:02 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

//-fsanitize=address

// void add_node(char *env)
// {
//     int     i;
//     int     j;
//     t_env   *e;

//     i = 0;
//     j = 0;
//     // e->next = NULL;
//     while (env[i] != '\0')
//     {
//         // if (env[i] != '=')
//         // {
//             e->value = &env[i];
//             printf("value: %s\n", e->value);
//         // }
//         // else if (env[i] == '=')
//         // {
//         //     j = i;
//         //     while(env[j])
//         //     {
//         //         e->path = &env[j];
//         //         printf("----%s\n", e->path);
//         //         j++;
//         //     }
//         // }
//         // e->next = *env;
//         i++;
//     }
// }


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

// struct Node* createNode(char  *val, char  *key)
// {
//     struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
//     newNode->key = key;
//     newNode->val = val;
//     newNode->next = NULL;
//     return newNode;
// }

// void insertNode(struct Node** head, char  *val, char  *key)
// {
//     struct Node* newNode = createNode(val, key);
//     if (*head == NULL) {
//         *head = newNode;
//     } else {
//         struct Node* temp = *head;
//         while (temp->next != NULL) {
//             temp = temp->next;
//         }
//         temp->next = newNode;
//     }
// }

// void displayList(struct Node* head)
// {
//     struct Node* temp = head;
//     while (temp != NULL) {
//         printf("%s", temp->key);
//         printf("%s \n", temp->val);
//         temp = temp->next;
//     }
//     // printf("\n");
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
    // head->key = NULL;
    // head->val = NULL;
    // head->next = NULL;
    (void)env;
    // execute();
    // printf("dddd");
    t_env   *e = malloc(sizeof(t_env));
    create_env(env, &head);
    // cd(env, head);
    // displayList(head);
    // int i = 0;
    // while(env[i])
    // {
    //     insertNode(&head, get_value(env[i]), get_key(env[i]));
    //     i++;
    // }
    // Display the linked list
    // displayList(head);

    // ft_ex_port(head, "_ee4=", "rrsssssrffg");
    // ft_ex_port(head, "salam" , "hello");
    // ft_ex_port(head, "salam" , "wdewferfre");
    // ft_ex_port(head, "sssssss4=" , "5452454");
    // ft_ex_port(head, "salam=" , "gggghello");
    // ft_ex_port(head, "ddddd",  "");
    // ft_ex_port(head, "ddfffffffddd",  "");
    // ft_ex_port(head, "dddrrrrrrdd",  "");
    // ft_ex_port(head, "dfrefref",  "");
    // ft_ex_port(head, "kkkkk",  "44444");
    // ft_ex_port(head, "fffff",  "jjjjj");
    // ft_ex_port(head, "fffff=",  "freer");
    // ft_ex_port(head, "fffff=",  "freer");
    // un_set(head, "fffff=");
    // un_set(head, "NUGET_XMLDOC_MODE=");
    // ft_ex_port(head, "fffff=",  "freer");

    // un_set(head, "TERM=");
        // displayList_export(head);
    
    printf("--------------------------------\n");
    displayList(head);

    // pwd();
    
    // get_env(env, e);
    // int    i = 0;
    // while(i < e->test)
    // {
    //     printf("%s", e->key[i]);
    //     printf("%s\n", e->value[i]);
    //     i++;
    // }
    // char    **arr = malloc(sizeof(char *) * e->test + 1);
    // char    **g_env = malloc(sizeof(char *) * e->test + 1);
    // i = 0;
    // while (i < e->test)
    // {
    //     arr[i] = str_join(e->key[i], e->value[i]);
    //     g_env[i] = ft_str_dup(arr[i]);
    //     free(arr[i]);
    //     i++;
    // }
    // i = 0;
    // while (i < e->test)
    // {
    //     printf("%s\n", g_env[i]);
    //     i++;
    // }
    // add_env(e,"test=rrrrr");
    // printf("----%d---\n", e->test);

    // printf("---- 2 ---\n");
    // i = 0;
    // while(i < e->test)
    // {
    //     // printf("%s=", e->key[i]);
    //     // printf("%s\n", e->value[i]);
    //     printf("%s", env[i]);
    //     i++;
    // }
    // char* value = getenv("HOME");
    // if (value != NULL) {
    //     printf("The value of HOME is: %s\n", value);
    // } else {
    //     printf("HOME environment variable is not set.\n");
    // }

    // char* name = "MY_VARIABLE";
    // char* v = "Hello, World!";
    // char* env = malloc(strlen(name) + strlen(v) + 2);
    // sprintf(env, "%s=%s", name, v);
    // if (putenv(env) == 0) {
    //     printf("%s\n", getenv(name));
    //     printf("Environment variable set successfully.\n");
    // } else {
    //     printf("Failed to set environment variable.\n");
    // }

    
    // free(env);
    // while(1);
    free(e);
    
    // free(e->key);
    // free(e->val);
    return 0;
}


