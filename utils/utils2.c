/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:25:45 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/21 22:26:45 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

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