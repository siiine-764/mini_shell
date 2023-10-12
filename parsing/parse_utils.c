/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:08:29 by hben-mes          #+#    #+#             */
/*   Updated: 2023/10/12 04:27:41 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	node_add(t_top_cmd *top, t_comm *comm)
{
	t_comm	*temp;

	temp = top->fst_cmd;
	if (temp == NULL)
	{
		top->fst_cmd = comm;
		top->size += 1;
		comm->nxt_comm = NULL;
		return ;
	}
	while (temp->nxt_comm)
		temp = temp->nxt_comm;
	temp->nxt_comm = comm;
	top->size += 1;
	comm->nxt_comm = NULL;
}

char	**ft_dup(char **av, char *val, int i)
{
	int		j;
	char	**t;

	t = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j < i - 1)
	{
		t[j] = av[j];
		j++;
	}
	t[j] = ft_strdup(val);
	t[j + 1] = NULL;
	free(av);
	return (t);
}

int	rederiction_handle(t_comm *red, t_tkn *tkn, t_top_cmd *top)
{
	if (syntax_handle(tkn->val, tkn, top) == 1)
		return (1);
	else if (tkn->tkn == T_HERDOC)
		redirection_add(red->heredoc, tkn);
	else
		redirection_add(red->redirection, tkn);
	return (0);
}
