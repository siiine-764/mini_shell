
#include "../MiniShell.h"

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

t_tkn	*ft_redirection(t_lxr *lxr, t_cata *env_list)
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

t_tkn	*handle_her(t_lxr *lxr, t_cata *env_list)
{
	if (ft_strncmp(&lxr->ctt[lxr->i], "<<", 2) == 0)
	{
		ft_move(lxr);
		ft_move(lxr);
		space_skip(lxr);
		if (lxr->ctt[lxr->i] == '\0' || \
			lxr->cmd == '<' || lxr->cmd == '>'
			|| lxr->cmd == '|')
			return (tkn_initialize(T_HEREDOC, NULL));
		return (tkn_initialize(T_HEREDOC, get_data(lxr, env_list, 0)));
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
