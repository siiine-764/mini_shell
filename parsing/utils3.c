/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:55:01 by hben-mes          #+#    #+#             */
/*   Updated: 2023/10/12 04:33:49 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cases_check(t_lxr *lxr)
{
	if (lxr->ctt[lxr->i] 
		&& lxr->cmd != ' ' && lxr->cmd != '$' 
		&& lxr->cmd != '\'' && lxr->cmd != '"' 
		&& lxr->cmd != '?' && lxr->cmd != '!' 
		&& (ft_isalnum(lxr->cmd) != 0 
			|| ft_isalpha(lxr->cmd) != 0 || lxr->cmd == '_'))
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
