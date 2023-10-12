/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:03:54 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:03:55 by mayache-         ###   ########.fr       */
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