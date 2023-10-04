/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:07:45 by hben-mes          #+#    #+#             */
/*   Updated: 2023/09/25 13:07:45 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_initialize(t_top_cmd *top)
{
	top->fst_cmd= NULL;
	top->size = 0;
}

void	free_tokens(t_tkn_top *top)
{
	t_tkn	*temp;

	while (top->fst_tkn)
	{
		temp = top->fst_tkn;
		top->fst_tkn = top->fst_tkn->nxt;
		free(temp->val);
		free(temp);
	}
	free(top);
}

void	all_free(t_top_cmd *top)
{
	int			i;		
	t_comm		*j;

	while (top->fst_cmd)
	{
		i = 0;
		while (top->fst_cmd->flags[i])
		{
			free(top->fst_cmd->flags[i]);
			i++;
		}
		free(top->fst_cmd->flags);
		free_tokens(top->fst_cmd->heredoc);
		free_tokens(top->fst_cmd->redirection);
		j = top->fst_cmd;
		top->fst_cmd = top->fst_cmd->nxt_comm;
		free(j);
	}
	free(top);
}