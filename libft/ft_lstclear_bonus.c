/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:14:12 by mayache-          #+#    #+#             */
/*   Updated: 2022/10/19 13:19:26 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	lstsize(t_env *lst)
{
	int	sz;

	sz = 0;
	while (lst)
	{
		sz++;
		lst = lst -> nxt;
	}
	return (sz);
}

void	lstdelone(t_env *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst -> ctt);
		free(lst);
	}
}

void	ft_lstclear(t_env **lst, void (*del)(void*))
{
	t_env	*cpynext;

	if (lst == NULL || !del)
		return ;
	while (*lst != NULL)
	{
		cpynext = (*lst)-> nxt;
		lstdelone(*lst, del);
		*lst = cpynext;
	}
}
