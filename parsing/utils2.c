/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:12:28 by hben-mes          #+#    #+#             */
/*   Updated: 2023/09/26 16:44:52 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_code(void)
{
	return(1);
	// return (g_global_vars.exit_code);
}

void	put_exit(int i)
{
	if (i == SYNTAX_ERROR_EXIT)
	{
		// g_global_vars.exit_code = i;
		printf("i in put exit : %d\n", i);
	}
	else
	{
		while (i > 255)
			i -= 256;
		// g_global_vars.exit_code = i;
		printf("i in put exit : %d\n", i);
	}
}

int	syntax_handle(char *data, t_tkn *tk, t_top_cmd *top)
{
	if (data == NULL)
	{
		free(tk);
		free(tk->data);
		all_free(top);
		printf("minishell:syntax error\n");
		put_exit(SYNTAX_ERROR_EXIT);
		return (1);
	}
	return (0);
}

int	ft_digitlen(long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*digit;
	long	nbr;
	int		bl;
	int		strlen;

	nbr = (long)n;
	bl = 0;
	strlen = ft_digitlen(nbr);
	digit = (char *)malloc(strlen + 1);
	if (digit == NULL)
		return (NULL);
	digit[strlen] = '\0';
	if (nbr < 0)
	{
		nbr *= -1;
		bl = 1;
	}
	while (strlen--)
	{
		digit[strlen] = (nbr % 10) + 48;
		nbr /= 10;
	}
	if (bl == 1)
		digit[0] = '-';
	return (digit);
}

char	*ft_strdup(const char *s1)
{
	char	*space;
	int		i;

	i = 0;
	space = (char *)malloc(ft_strlen(s1) + 1);
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

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_isdigit(int digit)
{
	if (digit >= '0' && digit <= '9')
		return (1);
	return (0);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && n > i)
	{
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	if (n > i)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
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


int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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