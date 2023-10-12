/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:01:34 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 04:43:12 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(t_env *env_list, char *command)
{
	t_p_data	data;

	data.path = find_env(env_list, "PATH");
	if (data.path == NULL || command == NULL)
		return (NULL);
	data.i = -1;
	data.p_comm = ft_split(data.path, ':');
	free(data.path);
	while (data.p_comm[++data.i])
	{
		data.temp = data.p_comm[data.i];
		data.p_comm[data.i] = ft_strjoin(data.p_comm[data.i], "/");
		free(data.temp);
		data.temp = data.p_comm[data.i];
		data.p_comm[data.i] = ft_strjoin(data.p_comm[data.i], command);
		free(data.temp);
		if (access(data.p_comm[data.i], F_OK) == 0)
		{
			data.temp = ft_strdup(data.p_comm[data.i]);
			free_arry(data.p_comm);
			return (data.temp);
		}
	}
	free_arry(data.p_comm);
	return (NULL);
}

void	ft_error(char *i, char *l, int exit)
{
	ft_putstr_fd(i, STDERR_FILENO);
	ft_putendl_fd(l, STDERR_FILENO);
	e_code(exit);
}
