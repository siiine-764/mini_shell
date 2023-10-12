/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:04:42 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:04:42 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char *path, t_env *env_list, t_env *pub_list)
{
	if (path == NULL)
		cd_home(env_list, pub_list);
	else if (ft_strcmp(".", path) == 0)
		return ;
	else if (ft_strcmp("..", path) == 0)
	{
		cd_oldpwd(env_list, pub_list);
        if (chdir("..") == -1)
		{
			e_code(1);
			perror(path);
		}
		cd_newpwd(env_list, pub_list);
        return ;
	}
	else
	{
		cd_oldpwd(env_list, pub_list);
		if (chdir(path) == -1)
		{
			e_code(1);
			perror(path);
		}
		cd_newpwd(env_list, pub_list);
	}
}

int	run_cd(t_data data, t_comm *comm)
{
	(void)data;
	if (!ft_strcmp(comm->flags[0], "cd"))
	{
		ft_cd(comm->flags[1], data.env_list, data.pub_list);
		return (true);
	}
	return (false);
}
