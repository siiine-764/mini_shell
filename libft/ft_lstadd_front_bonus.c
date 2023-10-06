/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:36:30 by mayache-          #+#    #+#             */
/*   Updated: 2022/10/19 13:29:43 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_env **lst, t_env *new)
{
	if (lst != NULL && new != NULL)
	{
		new->nxt = *lst;
		*lst = new;
	}
}
