/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 00:57:54 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/20 22:46:56 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void    ft_ex_port(struct Node* head, char *add_key, char *add_val, char **env)
{
    int bl = 0;
    (void)env;

    char *strjoin = ft_strjoin(add_key, "=");
    if (!strjoin[0] && !add_val[0])
    {
        // displayList(head);
        displayList_export(head);
        // printf("setenv: invalid.");
        free(head);
        exit(0);
    }
    if (!ft_isalpha(strjoin[0]) && strjoin[0] != '_')
    {
        printf("export: `%s': not a valid identifier\n", strjoin);
        exit(1);    
    }
    struct Node* temp = head;

    while (temp != NULL)
    {
        // printf("temp :%s, add key %s\n",temp->key, strjoin );
        if(strcmp(temp->key, strjoin) == 0)
        {
            bl = 1;
            printf("------>this key is repeat<--------\n");
            strcpy(temp->val, add_val);
        }
        temp = temp->next;
    }
    if(bl == 0)
    {
        insertNode(&head, add_val, strjoin);
        // printf("--> val %s, key %s\n", head->val, head->key);
    }
    
    // create_env(env, &head);
    // displayList(head);
}

// export  env ok

// export dddd4d_ error ok

// export _ee4=ffgg work ok

// export a display a + env ok
