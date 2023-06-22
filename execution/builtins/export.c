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

void    ex_port(char *add_key, char *add_val)
{
    struct Node* head = NULL;

    insertNode(&head, get_value(add_key), get_key(add_val));
}