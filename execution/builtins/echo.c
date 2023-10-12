/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:05:06 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:05:06 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
