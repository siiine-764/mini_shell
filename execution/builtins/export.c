/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 00:57:54 by mayache-          #+#    #+#             */
/*   Updated: 2023/06/18 01:05:08 by mayache-         ###   ########.fr       */
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
    struct Node* temp = head;
    // int bl = 0;
    if (!add_key[0] || !add_val[0])
    {
        printf("setenv: invalid.");
        free(head);
        exit(1);
    }
    // printf("|||||||||||\n");
    // printf("|addkey %s|\n", add_key);
    // printf("|||||||||||\n");
    while (temp != NULL)
    {
        // printf("|||||||||||\n");
        // printf("|addkey %s|\n", temp->key);
        // printf("|||||||||||\n");
        //  if (ft_strstartswith(temp->key, add_key))
        if(strcmp(temp->key, add_key) == 0)
        {
            // bl = 1;
            // printf("yassine is here\n");
            strcpy(temp->val, add_val);
        }
        // printf("%s...... \n", temp-)
        // printf("%s.....", temp->key);
        // printf("%s...... \n", temp->val);
        temp = temp->next;
    }
    // ft_find_replace(head, add_key, add_val);
    // if(bl == 0)
    // {
        add_key = str_join(add_key, "=");
        insertNode(&head, add_val, add_key);
    // }

}
