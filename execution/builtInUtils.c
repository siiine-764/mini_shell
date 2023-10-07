#include "../minishell.h"

t_env	*get_env_list(char **i)
{
	t_env	*env_list;
	int		c;

	c = 0;
	env_list = ft_lstnew(ft_strdup(i[c++]));
	while (i[c])
		ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(i[c++])));
	return (env_list);
}

void	sort_list(t_env **env_list)
{
	t_env	*i;
	t_env	*j;
	char	*res;

	i = *env_list;
	while (i)
	{
		j = *env_list;
		while (j->nxt)
		{
			if (ft_strcmp(j->ctt, j->nxt->ctt) > 0)
			{
				res = j->ctt;
				j->ctt = j->nxt->ctt;
				j->nxt->ctt = res;
			}
			j = j->nxt;
		}
		i = i ->nxt;
	}
}

char	*join_join(char **temp)
{
	int		i;
	char	*c;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (temp[++i])
	{
		c = res;
		res = ft_strjoin(res, temp[i]);
		free(c);
		if (temp[i + 1])
		{
			c = res;
			res = ft_strjoin(res, "=");
			free(c);
		}
	}
	free_2d(temp);
	return (res);
}

char	*find_env(t_env *env_list, char *name)
{
	// int		i;
	char	*c;
	char	**j;
	char	*temp;

	temp = ft_strdup("");
	while (env_list)
	{	
		j = ft_split(env_list->ctt, '=');
		c = temp;
		temp = ft_strdup(j[0]);
		free(c);
		// i = 0;
		free_2d(j);
		if (!temp || !*temp)
			return (NULL);
		if (ft_strcmp(temp, name) == 0)
		{
			free(temp);
			return (join_join(ft_split(env_list->ctt, '=')));
		}
		env_list = env_list->nxt;
	}
	free(temp);
	return (NULL);
}


