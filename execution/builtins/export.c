/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 00:57:54 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/18 18:04:58 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

int		ft_strstartswith(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s2[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

void    ft_ex_port(struct Node* head, char *add_key, char *add_val)
{
    int bl = 0;
    if (!add_key[0] && !add_val[0])
    {
        // displayList(head);
        displayList_export(head);
        // printf("setenv: invalid.");
        free(head);
        exit(0);
    }
    if (!ft_isalpha(add_key[0]) && add_key[0] != '_')
    {
        printf("export: not an identifier: %s\n", add_key);
        exit(1);    
    }
    // if (add_key[0] && !add_val[0])
    // {
    //     // int d = 0;
    //     // printf("----> %s", add_key);
    //     // while (add_key[d] != '\0')
    //     // {       
    //         // printf("ddddddd");
    //         // printf("----->>>>> %d\n", d);
    //         // printf("---> %c\n", add_key[d]);
    //         if (!(add_key[0] >= 'a' && add_key[0] <= 'z')
    //                 && add_key[0] != '_'
    //                 && !(add_key[0] >= 'A' && add_key[0] <= 'Z')
    //         )
    //         {
    //             printf("export: not valid in this context: %s\n", add_key);
    //             exit(1);
    //         }
    //     //     d++;
    //     // }
    // }
    // displayList(head);
    // if (add_key[0] && add_val[0])
    // {
        
    // }
    struct Node* temp = head;
    // printf("|||||||||||\n");
    // printf("|addkey %s|\n", add_key);
    // printf("|||||||||||\n");

    
    while (temp != NULL)
    {
        // printf("|||||||||||\n");
        // printf("|||||||||||\n");
        // printf("|addkey %s|\n", add_key);

        //  if (ft_strstartswith (temp->key, add_key))
        if(strcmp(temp->key, add_key) == 0)
        {
            bl = 1;
            printf("------>yassine is here<--------\n");
            strcpy(temp->val, add_val);
        }
        // printf("%s...... \n", temp-)
        // printf("%s.....", temp->key);
        // printf("%s...... \n", temp->val);
        temp = temp->next;
    }
    // ft_find_replace(head, add_key, add_val);
    if(bl == 0)
    {
        add_key = str_join(add_key, "=");
        insertNode(&head, add_val, add_key);
    }
    displayList_export(head);
}


// export  env ok

// export dddd4d_ error ok

// export _ee4=ffgg work ok

// export a display a + env ok
