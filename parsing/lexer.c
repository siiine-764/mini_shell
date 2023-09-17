
#include "../MiniShell.h"

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

t_tkn	*tkn_nxt(t_lxr *lxr, t_cata *env_list)
{
	while (lxr->i < ft_strlen(lxr->ctt))
	{
		if (lxr->cmd == ' ')
			space_skip(lxr);
		else if (lxr->cmd == '|')
		{
			ft_move(lxr);
			space_skip(lxr);
			return (tkn_initialize(T_PIPE, ""));
		}
		else if (lxr->cmd == '"' || lxr->cmd == '\'')
			return (tkn_initialize(T_WORD, get_data(lxr, env_list, 1)));
		else if (ft_strncmp(&lxr->ctt[lxr->i], "<<", 2) == 0 || \
			ft_strncmp(&lxr->ctt[lxr->i], ">>", 2) == 0)
			return (handle_her(lxr, env_list));
		else if (lxr->cmd == '<' || lxr->cmd == '>')
			return (ft_redirection(lxr, env_list));
		else
			return (tkn_initialize(T_WORD, get_data(lxr, env_list, 1)));
	}
	return (NULL);
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

char	*get_data(t_lxr *lxr, t_cata *env_list, int l)
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