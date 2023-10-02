/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aft_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:02:03 by hben-mes          #+#    #+#             */
/*   Updated: 2023/09/27 18:52:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cases_check(t_lxr *lxr)
{
	if (lxr->ctt[lxr->i] && \
		lxr->cmd != ' ' && lxr->cmd != '$' && \
		lxr->cmd != '\'' && lxr->cmd != '"' && \
		
		lxr->cmd != '?' && lxr->cmd != '!' && \
		(ft_isalnum(lxr->cmd) != 0 || \
		ft_isalpha(lxr->cmd) != 0 || lxr->cmd == '_'))
		return (1);
	else
		return (0);
}

char	*get_var(t_lxr *lxr, t_env *env_list)
{
	char	*l;
	char	*s;

	l = ft_strdup("");
	while (cases_check(lxr) == 1)
	{
		s = l;
		l = ft_strjoin(l, &lxr->cmd);
		free(s);
		ft_move(lxr);
	}
	s = find_env(env_list, l);
	if (s)
	{
		free(l);
		return (s);
	}
	else
	{
		free(l);
		free(s);
		s = ft_strdup("");
	}
	return (s);
}

char	*aft_dollar(t_lxr *lxr, t_env *env_list)
{
	char	*s;

	ft_move(lxr);
	if (lxr->cmd == '?')
	{
		s = ft_itoa(exit_code());
		ft_move(lxr);
	}
	else if (ft_isdigit(lxr->cmd) != 0 || lxr->cmd == '@' || lxr->cmd == '*')
	{
		ft_move(lxr);
		return (ft_strdup(""));
	}
	else
		s = get_var(lxr, env_list);
	return (s);
}

int	aft_dollar_check(t_lxr *lxr)
{
	if (ft_isalnum(lxr->ctt[lxr->i + 1]) != 0 \
		|| lxr->ctt[lxr->i + 1] == '?' )
		return (1);
	else if (lxr->ctt[lxr->i + 1] == '@' || \
		lxr->ctt[lxr->i + 1] == '*')
		return (1);
	else if (lxr->ctt[lxr->i + 1] == '_')
		return (1);
	return (0);
}