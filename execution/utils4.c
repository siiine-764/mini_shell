/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:01:29 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 04:43:04 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_frst_cmd_before_herdoc(t_data *data, t_info my_info)
{
	close(my_info.fd[0]);
	dup2(my_info.fd[1], STDOUT_FILENO);
	exect(data, data->comm, my_info.frame);
}

void	exec_last_command_before_heredoc(t_data *data, t_info my_info)
{
	if (data->comm->redirection->fst_tkn == NULL && data->comm->nxt_comm)
		dup2(my_info.fd[1], STDOUT_FILENO);
	else
		close(my_info.fd[1]);
	close(my_info.fd[0]);
	dup2(my_info.temp_fd, STDIN_FILENO);
	exect(data, data->comm, my_info.frame);
}

void	exec_other_cmd_before_herdoc(t_data *data, t_info my_info)
{
	close(my_info.fd[0]);
	dup2(my_info.fd[1], STDOUT_FILENO);
	dup2(my_info.temp_fd, STDIN_FILENO);
	exect(data, data->comm, my_info.frame);
}
