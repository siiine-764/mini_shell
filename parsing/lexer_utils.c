/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:06:32 by hben-mes          #+#    #+#             */
/*   Updated: 2023/09/25 13:06:32 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
t_tkn	*ft_redirection(t_lxr *lxr, t_env *env_list)
{
	if (lxr->cmd == '<')
	{
		ft_move(lxr);
		space_skip(lxr);
		if (lxr->ctt[lxr->i] == '\0' || lxr->cmd == '<' || \
			lxr->cmd == '>')
		return (tkn_initialize(T_IN, NULL));
		return (tkn_initialize(T_IN, get_data(lxr, env_list, 1)));
	}
	else
	{

		ft_move(lxr);
		space_skip(lxr);
		if (lxr->ctt[lxr->i] == '\0' || \
			lxr->cmd == '<' || lxr->cmd == '>')
			return (tkn_initialize(T_OUT, NULL));
		return (tkn_initialize(T_OUT, get_data(lxr, env_list, 1)));
	}
}

t_tkn	*handle_her(t_lxr *lxr, t_env *env_list)
{
	if (ft_strncmp(&lxr->ctt[lxr->i], "<<", 2) == 0)
	{
		ft_move(lxr);
		ft_move(lxr);
		space_skip(lxr);
		if (lxr->ctt[lxr->i] == '\0' || \
			lxr->cmd == '<' || lxr->cmd == '>'
			|| lxr->cmd == '|')
			return (tkn_initialize(T_HERDOC, NULL));
		return (tkn_initialize(T_HERDOC, get_data(lxr, env_list, 0)));
	}
	else
	{
		ft_move(lxr);
		ft_move(lxr);
		space_skip(lxr);
		if (lxr->ctt[lxr->i] == '\0' || \
			lxr->cmd == '<' || lxr->cmd == '>'
			|| lxr->cmd == '|')
			return (tkn_initialize(T_APPEND, NULL));
		return (tkn_initialize(T_APPEND, get_data(lxr, env_list, 1)));
	}
}
