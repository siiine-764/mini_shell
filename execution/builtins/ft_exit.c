/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:18:50 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/09 23:18:50 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(char *var, char flag)
{
	int	e;

	if (var == NULL)
	{
		set_exit_code(0);
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
			set_exit_code(e);
			return ;
		}
		printf("exit\n");
		g_global_data.e = e;
		set_exit_code(e);
		exit(e);
	}
}

bool	run_exit(t_data data, t_comm *comm)
{
	if (!ft_strcmp(comm->flags[0], "exit"))
	{
		if (data.comm_num == 1)
		{
			ft_exit(comm->flags[1], '\0');
		}
		else
			ft_exit(comm->flags[1], 'p');
		return (true);
	}
	return (false);
}