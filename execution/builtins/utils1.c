/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:04:02 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:04:10 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*get_env(char **i)
{
	t_env	*env_list;
	int		c;

	c = 0;
	env_list = ft_lstnew(ft_strdup(i[c++]));
	while (i[c])
		ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(i[c++])));
	return (env_list);
}

void	sort_env(t_env **env_list)
{
	t_env	*i;
	t_env	*j;
	char	*res;

	i = *env_list;
	while (i)
	{
		j = *env_list;
		while (j->nxt)
		{
			if (ft_strcmp(j->ctt, j->nxt->ctt) > 0)
			{
				res = j->ctt;
				j->ctt = j->nxt->ctt;
				j->nxt->ctt = res;
			}
			j = j->nxt;
		}
		i = i ->nxt;
	}
}
