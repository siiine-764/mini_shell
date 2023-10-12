/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:34:32 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/10 18:34:32 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_heredoc(t_comm **comm)
{
	char	*l;

	if ((*comm)->heredoc->fst_tkn == NULL
		|| (*comm)->heredoc->fst_tkn->nxt == NULL)
		return ;
	while (*comm)
	{
		if ((*comm)->heredoc->fst_tkn->nxt == NULL)
			return ;
		while (true)
		{
			l = readline(">");
			if (l == NULL
				|| ft_strcmp(l, (*comm)->heredoc->fst_tkn->val) == 0)
				break ;
			free(l);
		}
		(*comm)->heredoc->fst_tkn = (*comm)->heredoc->fst_tkn->nxt;
	}
}

int	herdoc_outside_pipe(t_data *data, t_comm *comm)
{
	t_frame	frame_temp;
	t_frame	frame;

	open_heredoc(&comm);
	unlink("/tmp/temp");
	frame.fd_in = open("/tmp/temp", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (comm->heredoc->fst_tkn == NULL)
		return (false);
	read_for_heredoc(comm, frame.fd_in);
	frame_temp = open_fls(*data->comm->redirection);
	if (frame_temp.fd_in == -1 || frame_temp.fd_out == -1)
	{
		e_code(1);
		return (true);
	}
	frame.fd_out = dup(frame_temp.fd_out);
	if (frame_temp.fd_in != STDIN_FILENO)
		frame.fd_in = dup(frame_temp.fd_in);
	else
		frame.fd_in = dup(frame.fd_in);
	if (!chck_built_in_cmd(data, comm, frame))
		ft_execute(comm, data, frame);
	wait(NULL);
	unlink("/tmp/temp");
	return (true);
}
