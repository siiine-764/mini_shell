/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 00:57:54 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/21 21:07:26 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void    ft_ex_port(struct Node* head, char *add_key, char *add_val, char **env)
{
    int bl = 0;
    (void)env;

    if (!add_key[0] && !add_val[0])
    {
        displayList_export(head);
        // free(head);
        exit(0);
    }
    char *strjoin = ft_strjoin(add_key, "=");
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
}

// export  env ok

// export dddd4d_ error ok

// export _ee4=ffgg work ok

// export a display a + env ok
