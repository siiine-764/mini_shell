/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aft_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:05:44 by hben-mes          #+#    #+#             */
/*   Updated: 2023/10/03 23:05:44 by hben-mes         ###   ########.fr       */
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


int	get_exit_code(void)
{
	return (g_global_data.e);
}


char	*aft_dollar(t_lxr *lxr, t_env *env_list)
{
	char	*s;

	ft_move(lxr);
	if (lxr->cmd == '?')
	{
		s = ft_itoa(get_exit_code());
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