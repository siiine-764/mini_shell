/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:21:11 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/09 17:21:11 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	add_variable(t_comm *comm, t_data *data, char **s, int j)
{
	if (is_variable(comm->flags[j]))
	{
		if (s[1] == NULL)
		{
			add_unexisted_variable(comm, data, s, j);
			// return (0);
		}
		// else
		if (ft_getenv(data->env_list, s[0]) == NULL)
		{
			if (ft_getenv(data->pub_list, s[0]) != NULL)
			{
				ft_unset(&data->pub_list, s[0]);
				add_unexisted_variable(comm, data, s, j);
			}
			else
			{
				add_unexisted_variable(comm, data, s, j);
			}
		}
		else
		{
			add_existed_variable(comm, data, s, j);
		}
		return (0);
	}
	return (0);
}

void	add_non_variable(t_comm *comm, t_data *data, char **s, int j)
{
	if (ft_getenv(data->pub_list, s[0]) == NULL)
	{
		ft_lstadd_back(&(data)->pub_list,
			ft_lstnew(ft_strdup(comm->flags[j])));
		// sort_list(&data->pub_list);
	}
}

void	show_export_error( int *flag, int j, t_comm *comm)
{
	if (*flag == 0)
	{
		ft_error(comm->flags[j], " :EXPORT: IDENTIFIER DOSEN'T EXIST", 1);
		*flag = 1;
	}
}

void	add_properly_named_word(t_comm *comm, t_data *data, int j)
{
	char	**s;
	int		i;

	s = ft_split(comm->flags[j], '=');
	if (add_variable(comm, data, s, j) == 1)
		add_non_variable(comm, data, s, j);
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

