/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:22:19 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/21 22:25:24 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			reue;
	unsigned char	*wut;

	reue = 0;
	wut = b;
	while (len > reue)
	{
		wut[reue] = (unsigned char)c;
		reue++;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_memset(str, 0, count * size);
	return (str);
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

int str_len(char *env)
{
    int len = 0;

    while (env[len])
    {   
        len++;
    }
    return (len);
}
