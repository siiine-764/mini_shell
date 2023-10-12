/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtInUtils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:05:17 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:05:17 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_join(char **temp)
{
	int		i;
	char	*c;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (temp[++i])
	{
		c = res;
		res = ft_strjoin(res, temp[i]);
		free(c);
		if (temp[i + 1])
		{
			c = res;
			res = ft_strjoin(res, "=");
			free(c);
		}
	}
	free_arry(temp);
	return (res);
}

char	*find_env(t_env *env_list, char *name)
{
	char	*c;
	char	**j;
	char	*temp;

	temp = ft_strdup("");
	while (env_list)
	{	
		j = ft_split(env_list->ctt, '=');
		c = temp;
		temp = ft_strdup(j[0]);
		free(c);
		free_arry(j);
		if (!temp || !*temp)
			return (NULL);
		if (ft_strcmp(temp, name) == 0)
		{
			free(temp);
			return (join_join(ft_split(env_list->ctt, '=')));
		}
		env_list = env_list->nxt;
	}
	free(temp);
	return (NULL);
}


