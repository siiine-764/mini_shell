/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:52:43 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/18 18:05:11 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

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