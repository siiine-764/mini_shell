/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:27:28 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/27 20:25:49 by mayache-         ###   ########.fr       */
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*srcorigen;
	unsigned char	*dstcpy;
	size_t			i;

	i = 0;
	dstcpy = (unsigned char *)dst;
	srcorigen = (unsigned char *)src;
	if (dstcpy == (void *)0 && srcorigen == (void *)0)
		return (NULL);
	while (i < n)
	{
		dstcpy[i] = srcorigen[i];
		i++;
	}
	return (dstcpy);
}
