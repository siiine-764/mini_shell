/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:53:39 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/09 14:53:39 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	heredoc_exist(t_data *data)
{
	while (data->comm)
	{
		if (data->comm->heredoc->fst_tkn != NULL)
			return (true);
		data->comm = data->comm->nxt_comm;
	}
	return (false);
}

int	count_commands_before_heredoc(t_comm *comm)
{
	int	i;

	i = 0;
	while (comm && comm->heredoc->fst_tkn == NULL )
	{
		comm = comm->nxt_comm;
		i += 1;
	}
	return (i);
}

void	check_before_heredoc_commands(t_data *data, t_info my_info, int i)
{
	if (i == 0)
		exec_first_command_before_heredoc(data, my_info);
	else if (i == my_info.size - 1)
		exec_last_command_before_heredoc(data, my_info);
	else
		exec_other_command_before_heredoc(data, my_info);
}

void	run_commands_before_heredoc(t_data *data, t_info my_info, int i)
{
	g_global_data.pid = fork();
	if (g_global_data.pid == 0)
	{
		check_before_heredoc_commands(data, my_info, i);
		exit(0);
	}
}

void	exec_commands_before_heredoc(t_data *data)
{
	int		j;
	int		sts;
	t_info	my_info;

	j = 0;
	my_info.size = count_commands_before_heredoc(data->top->fst_cmd);
	my_info.ids = malloc(sizeof(int) * my_info.size);
	data->comm = data->top->fst_cmd;
	while (j < my_info.size && data->comm)
	{
		my_info.frame.fd_in = STDIN_FILENO;
		my_info.frame.fd_out = STDOUT_FILENO;
		pipe(my_info.fd);
		run_commands_before_heredoc(data, my_info, j);
		my_info.ids[j++] = g_global_data.pid;
		data->comm = data->comm->nxt_comm;
		my_info.temp_fd = dup(my_info.fd[0]);
		close_pipe(my_info.fd);
	}
	while (--j >= 0)
	{
		waitpid(my_info.ids[j], &sts, j);
	}
	free(my_info.ids);
}
