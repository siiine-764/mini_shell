/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:02:42 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:02:42 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	e_code(int i)
{
	if (i == SYNTAX_ERROR_EXIT)
		g_global_data.e = i;
	else
	{
		while (i > 255)
			i -= 256;
		g_global_data.e = i;
	}
}

int	check_redirection(t_data *data, t_comm *comm)
{
	if (comm->redirection->fst_tkn != NULL)
	{
		if (comm->redirection->fst_tkn->tkn == T_OUT)
			ft_redir_output_trunc(comm, data);
		else if (comm->redirection->fst_tkn->tkn == T_APPEND)
			ft_redir_output_append(comm, data);
		else if (comm->redirection->fst_tkn->tkn == T_IN)
			redir_input(comm, data);
		return (true);
	}
	else
		return (false);
}
