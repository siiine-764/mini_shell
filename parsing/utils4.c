/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 04:16:34 by hben-mes          #+#    #+#             */
/*   Updated: 2023/10/12 04:17:59 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_check(t_lxr *lxr, t_tkn *tkn, int l, t_top_cmd *top)
{
	free(tkn);
	space_skip(lxr);
	if (lxr->ctt[lxr->i] == '\0' || l == 0)
	{
		all_free(top);
		printf("minishell:syntax error\n");
		e_code(SYNTAX_ERROR_EXIT);
		return (1);
	}
	return (0);
}

int	token_check(t_tkn *tkn, t_comm *red, int *i, t_top_cmd *top)
{
	if (tkn->tkn == 0)
	{
		if (syntax_handle(tkn->val, tkn, top) == 1)
			return (1);
		red->flags = ft_dup(red->flags, tkn->val, *i);
		*i += 1;
		free(tkn->val);
		free(tkn);
	}
	else if (tkn->tkn >= 1 && tkn->tkn <= 4)
	{
		if (rederiction_handle(red, tkn, top) == 1)
			return (1);
	}
	return (0);
}

char	*utils_str(t_lxr *lxr)
{
	char	*s;

	ft_move(lxr);
	s = ft_strdup(&lxr->cmd);
	ft_move(lxr);
	return (s);
}
