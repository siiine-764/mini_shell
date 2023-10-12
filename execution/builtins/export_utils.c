/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:04:55 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:04:55 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_variable(t_comm *comm, t_data *data, char **s, int j)
{
	if (is_variable(comm->flags[j]))
	{
		if (ft_getenv(data->env_list, s[0]) == NULL)
		{
			if (ft_getenv(data->pub_list, s[0]) != NULL)
			{
				ft_un_set(&data->pub_list, s[0]);
				add_un_val(comm, data, s, j);
			}
			else
			{
				add_un_val(comm, data, s, j);
			}
		}
		else
		{	
			ft_un_set(&data->pub_list, s[0]);
			add_val(comm, data, s, j);
		}
		return (1);
	}
	return (0);
}

void	add_non_variable(t_comm *comm, t_data *data, char **s, int j)
{
	if (ft_getenv(data->pub_list, s[0]) == NULL)
	{
		ft_lstadd_back(&(data)->pub_list,
			ft_lstnew(ft_strdup(comm->flags[j])));
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

void	add_val_d(t_comm *comm, t_data *data, int j)
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

