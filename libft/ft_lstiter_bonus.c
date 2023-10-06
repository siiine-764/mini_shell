/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:16:28 by mayache-          #+#    #+#             */
/*   Updated: 2022/10/19 14:22:00 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_env *lst, void (*f)(void *))
{
	t_env	*save;

	if (!lst)
		return ;
	save = lst;
	while (save)
	{
		f(save->ctt);
		save = save -> nxt;
	}
}
