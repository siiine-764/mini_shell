/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:01:32 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:47:38 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_temp_stdin(t_comm *comm)
{
	int		stdin_temp;
	char	*l;

	open_heredoc(&comm);
	stdin_temp = open("/tmp/temp", O_RDWR | O_TRUNC | O_CREAT, 0777);
	while (true)
	{
		l = readline(">");
		if (l == NULL || !ft_strcmp(l, comm->heredoc->fst_tkn->val))
		{
			if (l)
				free(l);
			break ;
		}
		ft_putendl_fd(l, stdin_temp);
		free(l);
	}
	return (stdin_temp);
}

void	check_out_files(int *fd_out, int *f_output)
{
	if (*fd_out == STDOUT_FILENO)
	{
		unlink("/tmp/temp_f_output");
		*fd_out = open("/tmp/temp_f_output",
				O_RDWR | O_TRUNC | O_CREAT,
				0777);
	}
	else
		*f_output = -1;
}

void	check_in_files(int *stdin_temp, int *fd_in)
{
	if (*fd_in == STDIN_FILENO)
	{
		close(*stdin_temp);
		*stdin_temp = open("/tmp/temp", O_RDONLY);
		*fd_in = dup(*stdin_temp);
	}
	else
		*fd_in = dup(*fd_in);
}
