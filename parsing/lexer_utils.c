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
			return (tkn_initialize(NULL, T_IN));
		return (tkn_initialize(get_data(lxr, env_list, 1), T_IN));
	}
	else
	{

		ft_move(lxr);
		space_skip(lxr);
		if (lxr->ctt[lxr->i] == '\0' || \
			lxr->cmd == '<' || lxr->cmd == '>')
			return (tkn_initialize(NULL, T_OUT));
		return (tkn_initialize(get_data(lxr, env_list, 1), T_OUT));
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
			return (tkn_initialize(NULL, T_HERDOC));
		return (tkn_initialize(get_data(lxr, env_list, 0), T_HERDOC));
	}
	else
	{
		ft_move(lxr);
		ft_move(lxr);
		space_skip(lxr);
		if (lxr->ctt[lxr->i] == '\0' || \
			lxr->cmd == '<' || lxr->cmd == '>'
			|| lxr->cmd == '|')
			return (tkn_initialize(NULL, T_APPEND));
		return (tkn_initialize(get_data(lxr, env_list, 1), T_APPEND));
	}
}
