/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:34:35 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/10 18:34:35 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_export_error(t_data *data, t_comm *comm)
{
	int	i;

	(void)data;
	i = 0;
	while (comm->flags[++i])
		if (!chck_name(comm->flags[i]))
			exit(1);
}

void	check_cd_errors(t_data *data, t_comm *comm)
{
	if (comm->flags[1] == NULL 
		|| ft_strcmp("~", comm->flags[1]) == 0)
		if (ft_getenv(data->env_list, "HOME") == NULL)
			exit(1);
}
