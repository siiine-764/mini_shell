/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:59:17 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/09 18:59:17 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	chck_echo(char *str, char flag, int fd, t_frame frame)
{
	if (flag == 'n')
	{
		if (fd != STDOUT_FILENO)
			ft_putstr_fd(str, fd);
		else
			ft_putstr_fd(str, frame.fd_out);
	}
	else
	{
		if (fd != STDOUT_FILENO)
			ft_putendl_fd(str, fd);
		else
			ft_putendl_fd(str, frame.fd_out);
	}
}

void	ft_echo(t_comm *comm, char *str, char flag, t_frame frame)
{
	int		fd;

	fd = open_fls(*comm->redirection).fd_out;
	if (fd == -1)
	{
		e_code(1);
		return ;
	}
	if (str == NULL)
	{
		write(fd, "\n", 2);
		return ;
	}
	chck_echo(str, flag, fd, frame);
	free(str);
	e_code(EXIT_SUCCESS);
}

int	run_echo(t_data data, t_comm *comm, t_frame frame)
{
	(void)data;
	if (ft_strcmp(comm->flags[0], "echo") == 0)
	{
		if (comm->flags[1] == NULL)
			ft_echo(comm, NULL, '0', frame);
		else if ((chck_echo_flag(comm->flags[1])))
			ft_echo(comm, ft_join_echo(comm->flags, 'n'), 'n', frame);
		else
			ft_echo(comm, ft_join_echo(comm->flags, '\0'), '\0', frame);
		return (true);
	}
	return (false);
}
