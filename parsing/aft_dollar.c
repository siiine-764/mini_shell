
#include "../MiniShell.h"

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

void	free_2d(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
}

char	*join_join(char **temp)
{
	int		i;
	char	*cmd;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (temp[++i])
	{
		cmd = res;
		res = ft_strjoin(res, temp[i]);
		free(cmd);
		if (temp[i + 1])
		{
			cmd = res;
			res = ft_strjoin(res, "=");
			free(cmd);
		}
	}
	free_2d(temp);
	return (res);
}

char	*find_env(t_cata *env_list, char *name)
{
	int		i;
	char	*cmd;
	char	**j;
	char	*temp;

	temp = ft_strdup("");
	while (env_list)
	{	
		j = ft_split(env_list->content, '=');
		cmd = temp;
		temp = ft_strdup(j[0]);
		free(cmd);
		i = 0;
		free_2d(j);
		if (!temp || !*temp)
			return (NULL);
		if (ft_strcmp(temp, name) == 0)
		{
			free(temp);
			return (join_join(ft_split(env_list->ctt, '=')));
		}
		env_list = env_list->next;
	}
	free(temp);
	return (NULL);
}

char	*get_var(t_lxr *lxr, t_cata *env_list)
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

int	exit_code(void)
{
	return (g_global_vars.exit_code);
}

char	*aft_dollar(t_lxr *lxr, t_list *env_list)
{
	char	*s;

	ft_move(lxr);
	if (lxr->cmd == '?')
	{
		s = ft_itoa(exit_code());
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