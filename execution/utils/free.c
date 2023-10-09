/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:47:50 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/09 22:47:50 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_2d(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
}

void	free_list(t_env *env)
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