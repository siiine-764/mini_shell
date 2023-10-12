/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:21:10 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/09 13:21:10 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_data data, t_comm *comm, t_frame frame)
{
	t_frame	fd;

	fd = open_fls(*comm->redirection);
	if (fd.fd_in == -1 || fd.fd_in == -1)
	{
		exit(1);
		return ;
	}
	while (data.env_list)
	{
		if (data.env_list->ctt)
		{
			if (fd.fd_out == STDOUT_FILENO)
				ft_putendl_fd(data.env_list->ctt, frame.fd_out);
			else
				ft_putendl_fd(data.env_list->ctt, fd.fd_out);
		}
		data.env_list = data.env_list->nxt;
	}
}

int	run_env(t_data data, t_comm *comm, t_frame frame)
{
	if (!ft_strcmp(comm->flags[0], "env"))
	{
		ft_env(data, comm, frame);
		return (true);
	}
	return (false);
}

int	chck_name(char *str)
{
	return (ft_isalpha(str[0]) || str[0] == '_');
}

t_env	*ft_getenv(t_env *env_list, char *variable)
{
	char	*s;
	char	**j;

	while (env_list)
	{
		j = ft_split(env_list->ctt, '=');
		s = ft_strdup(j[0]);
		free_arry(j);
		if (!s || !*s)
			return (NULL);
		if (ft_strcmp(s, variable) == 0)
		{
			free(s);
			return (env_list);
		}
		env_list = env_list ->nxt;
		free(s);
	}
	return (NULL);
}

void	ft_setenv(t_env **env_list, char *key, char *val)
{
	t_env	*str;
	char	*res;
	char	*j;

	str = ft_getenv(*env_list, key);
	if (str == NULL)
	{
		res = ft_strjoin(key, "=");
		j = res;
		res = ft_strjoin(res, val);
		free(j);
		ft_lstadd_back(env_list, ft_lstnew(res));
	}
	else
	{
		ft_un_set(env_list, key);
		ft_setenv(env_list, key, val);
	}
}
