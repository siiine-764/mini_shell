/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:06:17 by hben-mes          #+#    #+#             */
/*   Updated: 2023/09/25 13:11:01 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniShell.h"

t_tkn	*tkn_initialize(char *data, int typ)
{
	t_tkn	*tkn;

	tkn = ft_calloc(1, sizeof(t_tkn));
	tkn->nxt = NULL;
	tkn->tkn = typ;
	tkn->data = data;
	return (tkn);
}

void	ft_move(t_lxr	*lxr)
{
	if (lxr->i < ft_strlen(lxr->ctt))
	{
		lxr->i += 1;
		lxr->cmd = lxr->ctt[lxr->i];
	}
}

void	space_skip(t_lxr	*lxr)
{
	while (lxr->ctt[lxr->i] == ' ' && lxr->ctt[lxr->i] != '\0')
		ft_move(lxr);
}

char	*join_str(t_lxr *lxr, t_cata *env_list, int l)
{
	char	*t;

	if (lxr->cmd == '\'' || lxr->cmd == '"')
	{
		t = str_collect(lxr, lxr->cmd, env_list, l);
		ft_move(lxr);
		return (t);
	}
	else
		return (unquoted_str(lxr, env_list, l));
}

char	*join_free(char *s, char *t)
{
	char	*temp;

	temp = s;
	s = ft_strjoin(s, t);
	free(t);
	free(temp);
	return (s);
}