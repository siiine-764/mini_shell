/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:18:50 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/09 23:18:50 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_ex_it(char *var, char flag)
{
	int	e;

	if (var == NULL)
	{
		e_code(0);
		exit(0);
	}
	if (!is_number(var))
	{
		if (flag != 'e')
			ft_error(var, ": argument not found\n", 255);
	}
	else
	{
		e = ft_atoi(var);
		if (flag != '\0')
		{
			e_code(e);
			return ;
		}
		printf("exit\n");
		g_global_data.e = e;
		e_code(e);
		exit(e);
	}
}

int	run_exit(t_data data, t_comm *comm)
{
	if (!ft_strcmp(comm->flags[0], "exit"))
	{
		if (data.comm_num == 1)
		{
			ft_ex_it(comm->flags[1], '\0');
		}
		else
			ft_ex_it(comm->flags[1], 'p');
		return (true);
	}
	return (false);
}