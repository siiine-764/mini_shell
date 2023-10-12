/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfr_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:03:17 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:03:17 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_cmd_before_herdoc(t_data *data, t_info my_info, int i)
{
	g_global_data.pid = fork();
	if (g_global_data.pid == 0)
	{
		chck_before_herdoc_cmd(data, my_info, i);
		exit(0);
	}
}

void	exec_cmd_before_herdoc(t_data *data)
{
	int		j;
	int		sts;
	t_info	my_info;

	j = 0;
	my_info.size = cnt_cmd(data->top->fst_cmd);
	my_info.ids = malloc(sizeof(int) * my_info.size);
	data->comm = data->top->fst_cmd;
	while (j < my_info.size && data->comm)
	{
		my_info.frame.fd_in = STDIN_FILENO;
		my_info.frame.fd_out = STDOUT_FILENO;
		pipe(my_info.fd);
		run_cmd_before_herdoc(data, my_info, j);
		my_info.ids[j++] = g_global_data.pid;
		data->comm = data->comm->nxt_comm;
		my_info.temp_fd = dup(my_info.fd[0]);
		close_pipe(my_info.fd);
		wait(NULL);
	}
	while (--j >= 0)
		waitpid(my_info.ids[j], &sts, j);
	free(my_info.ids);
}
