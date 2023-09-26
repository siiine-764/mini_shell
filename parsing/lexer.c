/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:07:59 by hben-mes          #+#    #+#             */
/*   Updated: 2023/09/25 13:07:59 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_tkn	*tkn_nxt(t_lxr *lxr, t_env *env_list)
{
	while (lxr->i < ft_strlen(lxr->ctt))
	{
		if (lxr->cmd == ' ')
			space_skip(lxr);
		else if (lxr->cmd == '|')
		{
			ft_move(lxr);
			space_skip(lxr);
			return (tkn_initialize("", T_PIPE));
		}
		else if (lxr->cmd == '"' || lxr->cmd == '\'')
			return (tkn_initialize(get_data(lxr, env_list, 1), T_WORD));
		else if (ft_strncmp(&lxr->ctt[lxr->i], "<<", 2) == 0 || \
			ft_strncmp(&lxr->ctt[lxr->i], ">>", 2) == 0)
			return (handle_her(lxr, env_list));
		else if (lxr->cmd == '<' || lxr->cmd == '>')
			return (ft_redirection(lxr, env_list));
		else
			return (tkn_initialize(get_data(lxr, env_list, 1), T_WORD));
	}
	return (NULL);
}

char	*get_data(t_lxr *lxr, t_env *env_list, int l)
{
	char	*s;
	char	*t;

	s = ft_strdup("");
	space_skip(lxr);
	while (lxr->ctt[lxr->i] && lxr->cmd != ' ' && \
		lxr->cmd != '>' && lxr->cmd != '<' && lxr->cmd != '|')
	{
		if (lxr->i < ft_strlen(lxr->ctt) - 1 && lxr->cmd == '$' && \
				(lxr->ctt[lxr->i + 1] == '\'' || \
			lxr->ctt[lxr->i + 1] == '"'))
			ft_move(lxr);
		else
		{
			t = join_str(lxr, env_list, l);
			if (t == NULL)
			{
				free(t);
				return (NULL);
			}
			s =join_free(s, t);
		}
	}
	return (s);
}