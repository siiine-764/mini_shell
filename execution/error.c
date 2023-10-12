/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:03:01 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:03:01 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_path(t_data *data, t_comm *comm)
{
	char	*p;

	p = get_path(data->env_list, comm->flags[0]);
	if (p == NULL)
		e_code(COMMAND_NOT_FOUND);
	else
		e_code(0);
	free(p);
}

void	check_files(t_tkn_top redirection)
{
	int	f_output;

	while (redirection.fst_tkn != NULL)
	{
		if (redirection.fst_tkn->tkn == T_IN)
		{
			f_output = open(redirection.fst_tkn->val, O_RDONLY);
			if (f_output == -1)
				e_code(1);
		}
		redirection.fst_tkn = redirection.fst_tkn->nxt;
	}
}
