/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:34:49 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/10 18:34:49 by mayache-         ###   ########.fr       */
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
			ft_redirect_output_trunc_mode(comm, data);
		else if (comm->redirection->fst_tkn->tkn == T_APPEND)
			ft_redirect_output_append_mode(comm, data);
		else if (comm->redirection->fst_tkn->tkn == T_IN)
			redirect_input(comm, data);
		return (true);
	}
	else
		return (false);
}
