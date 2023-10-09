/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:43:27 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/09 22:43:27 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_oldpwd(t_env *env_list, t_env *pub_list)
{
	char	buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	ft_setenv(&env_list, "OLDPWD", buff);
	ft_setenv(&pub_list, "OLDPWD", buff);
}

void	cd_newpwd(t_env *env_list, t_env *pub_list)
{
	char	new_wd[PATH_MAX];

	getcwd(new_wd, PATH_MAX);
	ft_setenv(&env_list, "PWD", new_wd);
	ft_setenv(&pub_list, "PWD", new_wd);
}

void	cd_home(t_env *env_list, t_env *pub_list)
{
	char *a;

	a = getenv("HOME");
	cd_oldpwd(env_list, pub_list);
    if (chdir(a)== -1)
    {
        perror("cd :HOME NOT FOUND");
        return ;
    }
	cd_newpwd(env_list, pub_list);
}

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
			set_exit_code(1);
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
			set_exit_code(1);
			perror(path);
		}
		cd_newpwd(env_list, pub_list);
	}
}

bool	run_cd(t_data data, t_comm *comm)
{
	(void)data;
	if (!ft_strcmp(comm->flags[0], "cd"))
	{
		ft_cd(comm->flags[1], data.env_list, data.pub_list);
		return (true);
	}
	return (false);
}
