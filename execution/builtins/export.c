/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 00:57:54 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/23 20:30:17 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void    ft_ex_port(struct Node* head, char *add_key, char *add_val, char **env)
{
    struct Node* temp = head;
    int bl = 0;
    (void)env;

    if (!add_key[0] && !add_val[0])
    {
        displayList_export(head);
        free(head);
        exit(0);
    }
    char *strjoin = ft_strjoin(add_key, "=");
    if (!ft_isalpha(strjoin[0]) && strjoin[0] != '_')
    {
        printf("export: `%s': not a valid identifier\n", strjoin);
        exit(1);    
    }

    while (temp != NULL)
    {
        if(strcmp(temp->key, strjoin) == 0)
        {
            bl = 1;
            printf("------>this key is repeat<--------\n");
            ft_strlcpy(temp->val, add_val, ft_strlen(temp->val));
        }
        temp = temp->next;
    }
    if(bl == 0)
    {
        insertNode(&head, add_val, strjoin);
    }
}

// export  env ok

// export dddd4d_ error ok

// export _ee4=ffgg work ok

// export a display a + env ok
