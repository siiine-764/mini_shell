/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:02:31 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:02:31 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redir_output_append(t_comm *comm, t_data *data)
{
	t_frame	frame;

	frame.heredoc_docs = -1;
	frame = open_fls(*comm->redirection);
	if (frame.fd_in == -1 || frame.fd_out == -1)
	{
		e_code(1);
		return ;
	}
	if (comm->flags[0] != NULL)
		if (!chck_built_in_cmd(data, comm, frame))
			ft_execute(comm, data, frame);
	e_code(EXIT_SUCCESS);
}

void	ft_redir_output_trunc(t_comm *comm, t_data *data)
{
	t_frame	frame;

	frame.heredoc_docs = -1;
	frame = open_fls(*comm->redirection);
	if (frame.fd_in == -1 || frame.fd_out == -1)
	{
		e_code(1);
		return ;
	}
	if (comm->flags[0] != NULL)
	{
		if (!chck_built_in_cmd(data, comm, frame))
			ft_execute(comm, data, frame);
	}
	e_code(EXIT_SUCCESS);
}

void	redir_input(t_comm *comm, t_data *data)
{
	t_frame	frame;

	frame.heredoc_docs = -1;
	frame = open_fls(*comm->redirection);
	if (frame.fd_out == -1 || frame.fd_in == -1)
	{
		e_code(1);
		return ;
	}
	else if (comm->flags[0] != NULL)
		if (!chck_built_in_cmd(data, comm, frame))
			ft_execute(comm, data, frame);
	e_code(EXIT_SUCCESS);
}

int	ft_herdoc(t_data *data, t_comm *comm, t_frame frame)
{
	int	output;
	int	stdin_temp;

	output = 42;
	stdin_temp = fill_temp_stdin(comm);
	frame = open_fls(*comm->redirection);
	if (frame.fd_in == -1 || frame.fd_out == -1)
	{
		e_code(1);
		return (0);
	}
	check_out_files(&output, &frame.fd_out);
	check_in_files(&frame.fd_in, &stdin_temp);
	frame.fd_out = dup(frame.fd_out);
	if (!chck_built_in_cmd(data, comm, frame))
	{
		ft_execute(comm, data, frame);
		wait(NULL);
		close(frame.fd_out);
	}
	unlink("tmp/temp");
	return (heredoc_return(output, frame));
}
