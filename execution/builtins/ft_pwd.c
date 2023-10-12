/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:04:29 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:04:30 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_pwd(t_data data, t_comm *comm, t_frame frame)
{
	(void)data;
	(void)frame;
	char	*cwd;
	char	buff[PATH_MAX];

	cwd = getcwd(buff, PATH_MAX);
	if (!ft_strcmp(comm->flags[0], "pwd"))
	{
		if (!cwd)
		{
			perror("minishell: pwd: ");
			exit(1);
		}
		printf("%s\n", cwd);
		return (true);
	}
	return (false);
}
