/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:52:43 by mayache-          #+#    #+#             */
/*   Updated: 2023/06/11 03:07:02 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

int str_len(char *env)
{
    int len = 0;

    while (env[len])
    {
        len++;
    }
    return (len);
}
