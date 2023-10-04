/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:51:25 by hben-mes          #+#    #+#             */
/*   Updated: 2023/10/03 23:47:14 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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
