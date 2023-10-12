/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_un_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:39:09 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 00:39:03 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void deleteNode(t_env **env_list, char* key)
{
    t_env *temp = *env_list;
    t_env *prev = NULL;

	char *str = find_env(*env_list, key);
	if (!str)
	{
		return ;
	}
	key = ft_strjoin(key, "=");
	key = ft_strjoin(key, str);
	if (temp != NULL && ft_strcmp(temp->ctt, key) == 0)
	{
		*env_list = temp->nxt;
		free(temp);
		return;
	}
	while (temp != NULL && ft_strcmp(temp->ctt, key) != 0)
	{
		prev = temp;
		temp = temp->nxt;
	}
	if (temp == NULL)
		return;
	prev->nxt = temp->nxt;
	free(temp);
	return;
}

void	ft_un_set(t_env **env_list, char *del)
{
	(void)del;

	if (!*env_list)
		return ;
	deleteNode(env_list, del);
}

int	run_unset(t_data *data, t_comm *comm)
{
	int	i;

	if (!ft_strcmp(comm->flags[0], "unset"))
	{
		i = 0;
		while (comm->flags[++i])
		{
			ft_un_set(&data->env_list, comm->flags[i]);
			ft_un_set(&data->pub_list, comm->flags[i]);
		}
		return (true);
	}
	return (false);
}
