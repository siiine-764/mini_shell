/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:59:14 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/09 18:59:14 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_for_echo(char **str, char flag)
{
	int		i;
	char	*j;
	char	*res;
	
	if (flag == 'n')
		i = 2;
	else
		i = 1;
	res = ft_strdup("");
	while (check_echo_flag(str[i]))
		i++;
	while (str[i])
	{
		j = res;
		res = ft_strjoin(res, str[i]);
		free(j);
		res = check_for_space(i, str, res);
		i++;
	}
	return (res);
}

char	*check_for_space( int i, char **str, char *res)
{
	char	*s;

	if (str[i + 1] && str[i][0] != '\0')
	{
		s = res;
		res = ft_strjoin(res, " ");
		free(s);
	}
	return (res);
}

int	check_echo_flag(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (ft_strcmp(str, "-") == 0)
		return (false);
	if (str[i++] != '-')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i += 1;
	}
	return (true);
}