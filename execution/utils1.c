/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:01:37 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:01:38 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cnt_cmd(t_comm *comm)
{
	int	i;

	i = 0;
	while (comm && comm->heredoc->fst_tkn == NULL)
	{
		comm = comm->nxt_comm;
		i += 1;
	}
	return (i);
}

void	chck_before_herdoc_cmd(t_data *data, t_info my_info, int i)
{
	if (i == 0)
		exec_frst_cmd_before_herdoc(data, my_info);
	else if (i == my_info.size - 1)
		exec_last_command_before_heredoc(data, my_info);
	else
		exec_other_cmd_before_herdoc(data, my_info);
}

int	get_len(t_comm *comm)
{
	int	i;

	i = 0;
	while (comm)
	{
		i += 1;
		comm = comm->nxt_comm;
	}
	return (i);
}

void	exect(t_data *data, t_comm *comm, t_frame frame)
{
	if (chck_built_in_cmd(data, comm, frame) == false)
	{
		if (!check_redirection(data, comm))
		{
			if (comm->heredoc->fst_tkn == NULL)
			{
				ft_execute(comm, data, frame);
				wait(NULL);
			}
		}
	}
}
