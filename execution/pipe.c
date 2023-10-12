/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:34:16 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/10 18:34:16 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	exec_after_heredoc(t_info *my_info, t_data *data, int *p)
// {
// 	pipe(my_info->fd);
// 	my_info->id = fork();
// 	if (my_info->id == 0)
// 	{
// 		if (my_info->i == 0)
// 			exec_first_node(data, *my_info);
// 		else if (my_info->i == my_info->size - 1)
// 			exec_last_node(data, *my_info);
// 		else
// 			exec_other_node(data, *my_info);
// 		exit(127);
// 	}
// 	my_info->ids[*p++] = my_info->id;
// 	my_info->frame.heredoc_docs = 42;
// 	my_info->temp_fd = dup(my_info->fd[0]);
// 	close(my_info->fd[0]);
// 	close(my_info->fd[1]);
// }

void	run_herdoc(int *fd_heredoc, t_data *data, t_info my_info)
{
	if (data->comm->nxt_comm)
	{
		*fd_heredoc = ft_herdoc(data,
				data->comm, my_info.frame);
		wait(NULL);
	}
	else
	{
		herdoc_outside_pipe(data, data->comm);
	}
}

void	ft_loop(t_data *data, t_info my_info)
{
	int		sts;
	int		k;

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
	while (--k >= 0)
		waitpid(my_info.ids[k], &sts, k);
}

// int	check_heredoc(t_comm *comm)
// {
// 	while (comm)
// 	{
// 		if (comm->heredoc->fst_tkn != NULL)
// 			return (true);
// 		comm = comm->nxt_comm;
// 	}
// 	return (comm);
// }

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
		// e_code_inside_pipe(data, data->top->fst_cmd);
	}
	else
	{
		if (!herdoc_outside_pipe(data, data->comm))
			exect(data, data->comm, my_info.frame);
	}
	free(my_info.ids);
	g_global_data.pid = -1;
	// close_pipe(my_info.fd);
}
