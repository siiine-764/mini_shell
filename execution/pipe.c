/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:02:50 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:42:41 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_herdoc(int *fd_heredoc, t_data *data, t_info my_info)
{
	if (data->comm->nxt_comm)
	{
		*fd_heredoc = ft_herdoc(data,
				data->comm,
				my_info.frame);
		wait(NULL);
	}
	else
	{
		herdoc_outside_pipe(data, data->comm);
	}
}

void	ft_loop(t_data *data, t_info my_info)
{
	int	k;

	k = 0;
	my_info.size = get_len(data->comm);
	my_info.size -= cnt_cmd(data->comm);
	my_info.frame.heredoc_docs = 42;
	run_to_heredoc(&data->comm);
	while (data->comm)
	{
		my_info.frame.fd_in = STDIN_FILENO;
		my_info.frame.fd_out = STDOUT_FILENO;
		if (data->comm->heredoc->fst_tkn != NULL)
			run_herdoc(&my_info.frame.heredoc_docs, data, my_info);
		else
		{
			chck_cmd_order(data, &my_info);
			wait(NULL);
			close_pipe(my_info.fd);
			my_info.frame.heredoc_docs = 42;
		}
		my_info.ids[k++] = g_global_data.pid;
		my_info.i += 1;
		data->comm = data->comm->nxt_comm;
	}
	ft_wait_pid(my_info);
}

void	ft_wait_pid(t_info my_info)
{
	int	sts;
	int	k;

	k = -1;
	while (--k >= 0)
		waitpid(my_info.ids[k], &sts, k);
}

void	ft_pi_pe(t_data *data)
{
	t_info	my_info;

	my_info.frame.fd_in = STDIN_FILENO;
	my_info.frame.fd_out = STDOUT_FILENO;
	my_info.size = get_len(data->comm);
	my_info.ids = malloc(sizeof(int) * my_info.size);
	my_info.i = 0;
	if (my_info.size != 1)
	{
		ft_loop(data, my_info);
		exec_cmd_before_herdoc(data);
	}
	else
	{
		if (!herdoc_outside_pipe(data, data->comm))
			exect(data, data->comm, my_info.frame);
	}
	free(my_info.ids);
	g_global_data.pid = -1;
}
