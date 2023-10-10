/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:34:03 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/10 18:34:03 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_input_files(t_tkn_top redirection)
{
	int	fd_in;

	if (redirection.fst_tkn->tkn == T_IN)
	{
		fd_in = open(redirection.fst_tkn->val, O_RDONLY);
		if (fd_in == -1)
			perror(redirection.fst_tkn->val);
		return (fd_in);
	}
	return (INT_MIN);
}

int	open_trunc_mode_files(t_tkn_top redirection)
{
	int	fd_out;

	if (redirection.fst_tkn->tkn == T_OUT)
	{
		fd_out = open(redirection.fst_tkn->val, \
			O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd_out == -1)
			perror(redirection.fst_tkn->val);
		return (fd_out);
	}
	return (INT_MIN);
}

int	open_append_mode_files(t_tkn_top redirection)
{
	char	*file;
	int		output_fd;

	file = ft_strdup(redirection.fst_tkn->val);
	if (redirection.fst_tkn->tkn == T_APPEND)
	{
		output_fd = open(file,
				O_CREAT | O_APPEND | O_RDWR, 0644);
		if (output_fd == -1)
			perror(file);
		free(file);
		return (output_fd);
	}
	free(file);
	return (INT_MIN);
}

t_docs	init_files(t_tkn_top redirection)
{
	t_docs	my_files;

	my_files.in = open_input_files(redirection);
	my_files.trunc = open_trunc_mode_files(redirection);
	my_files.append = open_append_mode_files(redirection);
	return (my_files);
}

t_frame	open_files(t_tkn_top redirection)
{
	t_docs		my_files;
	t_frame		frame;

	init_contex(&frame);
	while (redirection.fst_tkn)
	{
		my_files = init_files(redirection);
		if (my_files.in == -1 || my_files.trunc == -1 || my_files.append == -1)
		{
			frame.fd_in = -1;
			frame.fd_out = -1;
			return (frame);
		}
		else
		{
			if (my_files.in != INT_MIN)
				frame.fd_in = my_files.in;
			if (my_files.trunc != INT_MIN)
				frame.fd_out = my_files.trunc;
			if (my_files.append != INT_MIN)
				frame.fd_out = my_files.append;
		}
		redirection.fst_tkn = redirection.fst_tkn->nxt;
	}
	return (frame);
}
