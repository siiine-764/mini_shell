/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:27:45 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 04:44:53 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word(char const *s, char c)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((s[0] != c && i == 0) || (s[i] != c && s[i - 1] == c && s[i]))
			j++;
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		index;
	char	**result;

	i = 0;
	if (!s)
		return (NULL);
	result = malloc((get_word(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	index = 0;
	while (index < get_word(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[i] != c && s[i])
			i++;
		result[index] = ft_substr(s, j, i - j);
		index++;
	}
	result[index] = NULL;
	return (result);
}
