/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:27:45 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/05 23:45:03 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int    get_parts(char const *s, char c)
{
    int    n;
    int    i;

    i = 0;
    n = 0;
    while (s[i])
    {
        if ((s[0] != c && i == 0) || (s[i] != c && s[i - 1] == c && s[i]))
            n++;
        i++;
    }
    return (n);
}

char    **ft_split(char const *s, char c)
{
    int        index;
    char    **result;
    int        i;
    int        o;

    i = 0;
    if (!s)
        return (NULL);
    result = malloc((get_parts (s, c) + 1) * sizeof(char *));
    if (!result)
        return (NULL);
    index = 0;
    while (index < get_parts (s, c))
    {
        while (s[i] == c && s[i])
            i++;
        o = i;
        while (s[i] != c && s[i])
            i++;
        result[index] = ft_substr(s, o, i - o);
        index++;
    }
    result[index] = NULL;
    return (result);
}

// int	cnt_words(const char *str, char delimiter)
// {
// 	int	cnt;
// 	int	i;

// 	i = 0;
// 	cnt = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != delimiter)
// 		{
// 			cnt++;
// 			while (str[i] && str[i] != delimiter)
// 				i++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (cnt);
// }

// int	sizew(char const *s, char c, int i)
// {
// 	int	sz;

// 	sz = 0;
// 	while (s[i] != c && s[i])
// 	{
// 		sz++;
// 		i++;
// 	}
// 	return (sz);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**stck;
// 	int		wrds;
// 	int		i;
// 	size_t	sz;
// 	size_t	count;

// 	i = 0;
// 	count = 0;
// 	if (!s)
// 		return (0);
// 	wrds = cnt_words(s, c);
// 	stck = (char **)malloc((wrds + 1) * sizeof(char *));
// 	if (stck == NULL)
// 		return (stck);
// 	while (i < wrds)
// 	{
// 		while (s[count] == c)
// 			count++;
// 		sz = sizew(s, c, count);
// 		stck[i] = ft_substr(s, count, sz);
// 		i++;
// 		count = count + sz;
// 	}
// 	stck[i] = 0;
// 	return (stck);
// }
