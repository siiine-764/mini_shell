/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:22:42 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 02:02:05 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_pwd(t_data data, t_comm *comm, t_frame frame)
// {
// 	t_frame		fm;
// 	char		dir[PATH_MAX];

// 	fm = open_fls(*comm->redirection);
// 	if (fm.fd_out == -1 || fm.fd_in == -1)
// 	{
// 		e_code(1);
// 		return ;
// 	}
// 	getcwd(dir, sizeof(dir));
// 	ft_setenv(&data.env_list, "PWD", dir);
// 	ft_setenv(&data.pub_list, "PWD", dir);
// 	if (fm.fd_out == STDOUT_FILENO)
// 		ft_putendl_fd(dir, frame.fd_out);
// 	else
// 		ft_putendl_fd(dir, fm.fd_out);
// 	e_code(EXIT_SUCCESS);
// }

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
	// if (!ft_strcmp(comm->flags[0], "pwd"))
	// {
	// 	ft_pwd(data, comm, frame);
	// 	return (true);
	// }
	return (false);
}
