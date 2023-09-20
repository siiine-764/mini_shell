/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:52:43 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/20 22:47:26 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int str_len(char *env)
{
    int len = 0;

    while (env[len])
    {   
        len++;
    }
    return (len);
}

char	*ft_str_dup(char *s1)
{
	char	*space;
	int		i;

	i = 0;
	space = malloc(sizeof(char *) * str_len(s1) + 1);
	if (space == NULL)
		return (NULL);
	while (s1[i])
	{
		space[i] = s1[i];
		i++;
	}
	space[i] = '\0';
	return (space);
}


char	*str_join(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	j = 0;
	i = 0;
	str = malloc(sizeof(char) * (str_len(s2) + str_len(s1) + 1));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
    {
		str[i] = s2[j];
        i++;
        j++;
    }
	str[i] = '\0';
	// free(s1);
	return (str);
}

char    **ft_arr_dup(char **origin)
{
    char	**arr;
	int		i;
	int		len;

	i = 0;
    len = 0;
    while(origin[len])
	{
        len++;
	}
	arr = malloc(sizeof(char *) * len + 1);
	if (arr == NULL)
		return (NULL);
	while (origin[i])
	{
		arr[i] = origin[i];
		i++;
	}
	return (arr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*reue;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (s1 && s2)
	{
		reue = (char *)malloc(lens2 + lens1 + 1);
		if (reue == NULL)
			return (NULL);
		ft_strlcpy(reue, s1, lens1 + 1);
		ft_strlcat(reue, s2, lens2 + lens1 + 1);
		return (reue);
	}
	return (0);
}

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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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
