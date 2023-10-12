/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:01:48 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:45:37 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_append_fls(t_tkn_top redirection)
{
	char	*file;
	int		output_fd;

	file = ft_strdup(redirection.fst_tkn->val);
	if (redirection.fst_tkn->tkn == T_APPEND)
	{
		output_fd = open(file,
				O_CREAT | O_APPEND | O_RDWR,
				0644);
		if (output_fd == -1)
			perror(file);
		free(file);
		return (output_fd);
	}
	free(file);
	return (INT_MIN);
}

t_docs	ft_init_fls(t_tkn_top redirection)
{
	t_docs	my_files;

	my_files.in = open_input_fls(redirection);
	my_files.trunc = open_trunc_fls(redirection);
	my_files.append = open_append_fls(redirection);
	return (my_files);
}

t_frame	open_fls(t_tkn_top redirection)
{
	t_docs	my_files;
	t_frame	frame;

	init_fd(&frame);
	while (redirection.fst_tkn)
	{
		my_files = ft_init_fls(redirection);
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
