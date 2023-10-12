/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:04:49 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:04:49 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	display_ex_port(t_comm *comm, t_data data, t_frame frame)
{
	frame = open_fls(*comm->redirection);
	if (frame.fd_in == -1 || frame.fd_out == -1)
	{
		e_code(1);	
		return ;
	}
	while (data.pub_list && data.pub_list->ctt != NULL)
	{
		if (frame.fd_out == STDOUT_FILENO)
		{
			ft_putstr_fd("declare -x  ", frame.fd_out);
			ft_putendl_fd(data.pub_list->ctt, frame.fd_out);
		}
		else
		{
			ft_putstr_fd("declare -x  ", frame.fd_out);
			ft_putendl_fd(data.pub_list->ctt, frame.fd_out);
		}
		data.pub_list = data.pub_list->nxt;
	}
}

int	run_ex_port(t_comm *comm, t_data *data, t_frame frame)
{
	int			flag;
	int			j;

	flag = 0;
	j = 0;
	if (ft_strcmp(comm->flags[0], "export"))
		return (false);
	if (comm->flags[1] == NULL)
		display_ex_port(comm, *data, frame);
	else
	{
		while (comm->flags[++j])
		{
			if (chck_name(comm->flags[j]))
				add_val_d(comm, data, j);
			else
				show_export_error(&flag, j, comm);
		}
	}
	return (true);
}
