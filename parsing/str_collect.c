/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_collect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:08:44 by hben-mes          #+#    #+#             */
/*   Updated: 2023/09/26 15:54:54 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prime_str_collect(t_lxr *lxr, t_env *env_list, char cmd, int l)
{
	char	*res;

	if (cmd == '"' && lxr->cmd == '$' && \
			lxr->i < ft_strlen(lxr->ctt) - 1 && \
			aft_dollar_check(lxr) == 1 && l == 1)
		return (aft_dollar(lxr, env_list));
	else if (lxr->cmd == '\\' && lxr->i < ft_strlen(lxr->ctt) - 1
		&& (lxr->ctt[lxr->i + 1] == '\\' \
		|| lxr->ctt[lxr->i + 1] == cmd \
		|| lxr->ctt[lxr->i + 1] == '$'))
	{
		ft_move(lxr);
		res = ft_strdup(&lxr->cmd);
		ft_move(lxr);
		return (res);
	}
	else
	{
		res = ft_strdup(&lxr->cmd);
		ft_move(lxr);
		return (res);
	}
}

char	*str_collect(t_lxr *lxr, t_env *env_list, char cmd, int l)
{
	char	*res;
	char	*s;
	char	*temp;

	s = ft_strdup("");
	ft_move(lxr);
	while (lxr->ctt[lxr->i] && lxr->cmd != cmd)
	{
		temp = s;
		res = prime_str_collect(lxr, env_list, cmd, l);
		s = ft_strjoin(s, res);
		free(res);
		free(temp);
	}
	if (lxr->cmd != cmd)
	{
		free(s);
		return (NULL);
	}
	return (s);
}
