/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:06:12 by hben-mes          #+#    #+#             */
/*   Updated: 2023/10/03 23:06:12 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_handle(char *val, t_tkn *t, t_top_cmd *top)
{
	(void)t;
	if (val == NULL)
	{
		free(t->val);
		all_free(top);
		printf("minishell:syntax error\n");
		e_code(SYNTAX_ERROR_EXIT);
		return (1);
	}
	return (0);
}

int	get_exit_code(void)
{
	return (g_global_data.e);
}

void	ft_initialize(t_top_cmd *top)
{
	top->fst_cmd = NULL;
	top->size = 0;
}

t_lxr	*lxr_initialize(char *ctt)
{
	t_lxr	*lxr;

	lxr = ft_calloc(1, sizeof(t_lxr));
	if (!lxr)
		return (NULL);
	lxr->ctt = ctt;
	lxr->i = 0;
	lxr->cmd = ctt[0];
	return (lxr);
}

void	redirection_add(t_tkn_top *top, t_tkn *t)
{
	t_tkn	*temp;

	temp = top->fst_tkn;
	if (temp == NULL)
	{
		top->fst_tkn = t;
		return ;
	}
	while (temp->nxt)
		temp = temp->nxt;
	temp->nxt = t;
}
