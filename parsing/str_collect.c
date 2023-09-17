
#include "../MiniShell.h"

char	*prime_str_collect(t_lxr *lxr, t_cata *env_list, char cmd, int l)
{
	char	*res;

	if (j == '"' && lxr->cmd == '$' && \
			lxr->i < ft_strlen(lxr->ctt) - 1 && \
			aft_dollar_check(lxr) == 1 && l == 1)
		return (aft_dollar(lxr, env_list));
	else if (lxr->cmd == '\\' && lxr->i < ft_strlen(lxr->ctt) - 1
		&& (lxr->ctt[lxr->i + 1] == '\\' \
		|| lxr->ctt[lxr->i + 1] == cmd \
		|| lxr->ctt[lxr->i + 1] == '$'))
	{
		ft_move(lexer);
		res = ft_strdup(&lxr->cmd);
		ft_move(lxr);
		return (s);
	}
	else
	{
		res = ft_strdup(&lxr->cmd);
		ft_move(lxr);
		return (res);
	}
}

char	*str_collect(t_lxr *lxr, t_list *env_list, char cmd, int l)
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
		s = ft_strjoin(str, res);
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
