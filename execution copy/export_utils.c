#include "../minishell_copy.h"

bool	add_variable(t_data *data, t_comm *comm, char **s, int j)
{
	if (is_variable(comm->flags[i]))
	{
		if (ft_getenv(data->env_list, s[0]) == NULL)
		{
			if (ft_getenv(data->pub_list, s[0]) != NULL)
			{
				ft_unset(&data->pub_list, s[0]);
				add_unexisted_variable(comm, data, s, j);
			}
			else
				add_unexisted_variable(comm, data, s, j);
		}
		else
			add_existed_variable(comm, data, j, s);
		return (true);
	}
	return (false);
}

void	add_non_variable(t_data *data, t_comm *comm, char **s, int j)
{
	if (ft_getenv(data->pub_list, s[0]) == NULL)
	{
		ft_lstadd_front(&(data)->pub_list,
			ft_lstnew(ft_strdup(comm->flags[i])));
		sort_list(&data->pub_list);
	}
}

void	show_export_error(t_comm *comm, int j, int *flag)
{
	if (*flag == 0)
	{
		ft_error(comm->flags[j], " :EXP: IDENTIFIER DOSEN'T EXIST", 1);
		*flag = 1;
	}
}

void	add_properly_named_word( t_data *data, t_comm *comm, int j)
{
	char	**s;
	int		i;

	s = ft_split(comm->flags[j], '=');
	if (!add_variable(comm, data, s, j))
		add_non_variable(comm, data, s, j);
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int	is_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && i - 1 >= 0 && str[i - 1] != '=')
			return (true);
		i++;
	}
	return (false);
}
