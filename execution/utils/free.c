/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:03:42 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:03:42 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_arry(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
}

void	free_lst(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->nxt;
		free(temp->ctt);
		free(temp);
		temp->ctt = NULL;
		temp = NULL;
	}
}