/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:02:02 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:02:02 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_other_node(t_data *data, t_info my_info)
{
	close(my_info.fd[0]);
	if (my_info.frame.heredoc_docs != 42)
	{
		close(my_info.temp_fd);
		close(my_info.frame.heredoc_docs);
		my_info.frame.heredoc_docs = open("/tmp/temp_f_output", O_RDONLY);
		dup2(my_info.frame.heredoc_docs, STDIN_FILENO);
		dup2(my_info.fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(my_info.fd[1], STDOUT_FILENO);
		dup2(my_info.temp_fd, STDIN_FILENO);
	}
	exect(data, data->comm, my_info.frame);
}

void	chck_cmd_order(t_data *data, t_info *my_info)
{
	pipe(my_info->fd);
	g_global_data.pid = fork();
	if (g_global_data.pid == 0)
	{
		if (my_info->i == 0)
			exec_first_node(data, *my_info);
		else if (my_info->i == my_info->size - 1)
			exec_last_node(data, *my_info);
		else
			exec_other_node(data, *my_info);
		exit(127);
	}
	my_info->temp_fd = dup(my_info->fd[0]);
}
