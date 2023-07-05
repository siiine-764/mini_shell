/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:25:08 by mayache-          #+#    #+#             */
/*   Updated: 2023/06/17 21:27:13 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"


int	number_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_isnum(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args_for_exit(char **args)
{
	if (args[0] && !args[1])
	{
		exit(0);
	}
	if (number_of_args(args) > 2)
	{
		printf("minishel: exit: too many arguments\n");
		return (1);
	}
	if (!ft_isnum(args[1]))
	{
		printf("exit: %s: numeric argument required\n", args[1]);
		exit(0);
	}
	return (0);
}

void    ex_it(void)
{
    printf("exit\n");
    // if (check_args_for_exit(cd->args))
    //     return (1);
    exit(0);
}