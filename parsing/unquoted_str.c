
#include "../MiniShell.h"

char	*utils_str(t_lxr *lxr)
{
	char	*s;

	ft_move(lxr);
	s= ft_strdup(&lxr->cmd);
	ft_move(lxr);
	return (s);
}

char	*str_put(t_lxr *lxr, t_cata *env_list, int l)
{
	char	*s;
	char	*d;

	if (lxr->cmd == '$' && lxr->i < ft_strlen(lxr->ctt) - 1 \
		&& aft_dollar_check(lxr) == 1 && l == 1)
		s = aft_dollar(lxr, env_list);
	else if (lxr->cmd == '~')
	{
		d = getenv("HOME");
		if (d == NULL)
			s = ft_strdup(&lxr->cmd);
		else
			s = ft_strdup(d);
		ft_move(lxr);
	}
	else if (lxr->cmd == '\\' && lxr->i < ft_strlen(lxr->ctt) - 1)
		s = utils_str(lxr);
	else if (lxr->cmd == '\\' && lxr->i == ft_strlen(lxr->ctt) - 1)
		return (NULL);
	else
	{
		s = ft_strdup(&lxr->cmd);
		ft_move(lxr);
	}
	return (s);
}

char	*unquoted_free(char *s, char *d)
{
	free(d);
	free(s);
	return (NULL);
}

char	*unquoted_str(t_lxr *lxr, t_cata *env_list, int l)
{
	char	*s;
	char	*d;

	s = ft_strdup("");
	while (lxr->ctt[lxr->i] && lxr->cmd != ' ' && \
		lxr->cmd != '\'' && lxr->cmd != '"' && lxr->cmd != '>' && \
		lxr->cmd != '<' && lxr->cmd != '|')
	{
		if (lxr->cmd == '&')
			return (unquoted_free(s, d));
		d = str_put(lxr, env_list, l);
		if (d == NULL)
		{
			free(s);
			return (NULL);
		}
		s = join_free(s, d);
	}
	return (s);
}
