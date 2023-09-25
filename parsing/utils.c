/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:04:08 by hben-mes          #+#    #+#             */
/*   Updated: 2023/09/25 13:12:41 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniShell.h"

void	free_2d(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
}

char	*join_join(char **temp)
{
	int		i;
	char	*cmd;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (temp[++i])
	{
		cmd = res;
		res = ft_strjoin(res, temp[i]);
		free(cmd);
		if (temp[i + 1])
		{
			cmd = res;
			res = ft_strjoin(res, "=");
			free(cmd);
		}
	}
	free_2d(temp);
	return (res);
}

char	*find_env(t_cata *env_list, char *name)
{
	int		i;
	char	*cmd;
	char	**j;
	char	*temp;

	temp = ft_strdup("");
	while (env_list)
	{	
		j = ft_split(env_list->content, '=');
		cmd = temp;
		temp = ft_strdup(j[0]);
		free(cmd);
		i = 0;
		free_2d(j);
		if (!temp || !*temp)
			return (NULL);
		if (ft_strcmp(temp, name) == 0)
		{
			free(temp);
			return (join_join(ft_split(env_list->ctt, '=')));
		}
		env_list = env_list->next;
	}
	free(temp);
	return (NULL);
}
