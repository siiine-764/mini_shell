/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:02:56 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:02:56 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_return(int f_output, t_frame frame)
{
	if (f_output == -1)
		return (0);
	else if (f_output == 0)
		return (frame.fd_in);
	else
		return (-1);
}

void	read_for_heredoc(t_comm *comm, int fd_in)
{
	char	*l;

	while (true)
	{
		l = readline(">");
		if (l == NULL || !ft_strcmp(l, comm->heredoc->fst_tkn->val))
		{
			if (l)
				free(l);
			break ;
		}
		ft_putendl_fd(l, fd_in);
		free(l);
	}
	close(fd_in);
	fd_in = open("/tmp/temp", O_RDONLY);
}
