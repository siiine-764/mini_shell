/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:08:36 by hben-mes          #+#    #+#             */
/*   Updated: 2023/09/25 13:08:36 by hben-mes         ###   ########.fr       */
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
		set_exit_code(SYNTAX_ERROR_EXIT);
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

int	node_load(t_comm *red, t_lxr *lxr, t_env *env_list, t_top_cmd *top)
{
	int			i;
	int			j;
	t_tkn		*tkn;

	tkn = tkn_nxt(lxr, env_list);
	i = 1;
	j = 0;
	while (tkn)
	{
		if (tkn->tkn < 5)
		{
			if (token_check(tkn, red, &i, top) == 1)
				return (1);
		}
		else if (tkn->tkn == 5)
		{
			if (pipe_check(lxr, tkn, j, top) == 1)
				return (1);
			break ;
		}
		j++;
		tkn = tkn_nxt(lxr, env_list);
	}
	return (0);
}

int	cmd_add(t_top_cmd *top, t_lxr *lxr, t_env *env_list)
{
	t_comm		*red;
	int			i;
	
	red = malloc(sizeof(t_comm));
	red->redirection = malloc(sizeof(t_tkn_top));
	red->heredoc = malloc(sizeof(t_tkn_top));
	red->heredoc->fst_tkn = NULL;
	red->redirection->fst_tkn = NULL;
	red->flags = malloc(sizeof(char *));
	red->flags[0] = NULL;
	if (node_load(red, lxr, env_list, top) == 1)
	{
		free(red->redirection);
		free(red->heredoc);
		i = -1;
		while (red->flags[++i])
			free(red->flags[i]);
		free(red->flags);
		free(red);
		return (1);
	}
	node_add(top, red);
	return (0);
}

t_top_cmd	*ft_execution(char *ctt, t_env *env_list)
{
	t_top_cmd	*cmd_top;
	t_lxr		*lxr;
	int			d;

	cmd_top = malloc(sizeof(t_top_cmd));
	ft_initialize(cmd_top);
	lxr = lxr_initialize(ctt);
	while (lxr->ctt[lxr->i])
	{
		d = cmd_add(cmd_top, lxr, env_list);
		if (d == 1)
		{
			free(lxr);
			return (NULL);
		}
	}
	free(lxr);
	return (cmd_top);
}
