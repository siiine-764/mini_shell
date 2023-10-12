/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:01:26 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:47:47 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_first_node(t_data *data, t_info my_info)
{
	close(my_info.fd[0]);
	dup2(my_info.fd[1], STDOUT_FILENO);
	exect(data, data->comm, my_info.frame);
}

void	exec_last_node(t_data *data, t_info my_info)
{
	close(my_info.fd[0]);
	close(my_info.fd[1]);
	if (my_info.frame.heredoc_docs != 42)
	{
		close(my_info.frame.heredoc_docs);
		my_info.frame.heredoc_docs = open("/tmp/temp_f_output", O_RDONLY, 0644);
		if (my_info.frame.heredoc_docs == 0)
		{
			unlink("/tmp/trash");
			my_info.frame.heredoc_docs = open("/tmp/trash", O_RDONLY | O_CREAT);
			dup2(my_info.frame.heredoc_docs, STDIN_FILENO);
		}
		else
		{
			dup2(my_info.frame.heredoc_docs, STDIN_FILENO);
		}
	}
	else
	{
		dup2(my_info.temp_fd, STDIN_FILENO);
	}
	exect(data, data->comm, my_info.frame);
}
