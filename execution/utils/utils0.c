/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:52:43 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/21 22:28:25 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lensrc;

	i = 0;
	lensrc = ft_strlen(src);
	if (dstsize == 0)
		return (lensrc);
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (lensrc);
}


size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstlen > dstsize)
		return (srclen + dstsize);
	while (src[i] && dstlen < dstsize && i < (dstsize - dstlen - 1))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}


int	cnt_words(const char *str, char delimiter)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] != delimiter)
		{
			cnt++;
			while (str[i] && str[i] != delimiter)
				i++;
		}
		else
			i++;
	}
	return (cnt);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*moschi;

	i = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	moschi = (char *)malloc(len + 1);
	if (moschi == NULL)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (i < len)
		{
			moschi[i] = s[start + i];
			i++;
		}
	}
	moschi[i] = '\0';
	return (moschi);
}

char	**ft_split(char const *s, char c)
{
	char	**stck;
	int		wrds;
	int		i;
	size_t	sz;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	wrds = cnt_words(s, c);
	stck = (char **)malloc((wrds + 1) * sizeof(char *));
	if (stck == NULL)
		return (stck);
	while (i < wrds)
	{
		while (s[count] == c)
			count++;
		sz = sizew(s, c, count);
		stck[i] = ft_substr(s, count, sz);
		i++;
		count = count + sz;
	}
	stck[i] = 0;
	return (stck);
}
