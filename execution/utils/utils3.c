/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:27:28 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/21 22:28:30 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	sizew(char const *s, char c, int i)
{
	int	sz;

	sz = 0;
	while (s[i] != c && s[i])
	{
		sz++;
		i++;
	}
	return (sz);
}
