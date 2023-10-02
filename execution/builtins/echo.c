/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:23:21 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/26 22:08:49 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int	check_flag_n(char *flg)
{
	int	i;

	i = 1;
	if (flg[0] != '-')
		return (0);
	while (flg[i])
	{
		if (flg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strrchr(const char *s, int c)
{
	int	len;
    int i;
    
    i = 0;
	len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)&s[len]);
	while (i < len)
    {
		if (s[i] == (char)c)
        {
            i++;
			return ((char *)&s[i]);
        }
        i++;
    }
	return (0);
}

void    e_cho(char **arr, char *flag)
{
    int i;
    int flg;
    char *result;

    flg = 0;
    i = 1;
    if (check_flag_n(flag) == 1)
        flg = 1;
    while (arr[i])
    {
        if (arr[i][0] != '$')
            printf("%s", arr[i]);
        if (arr[i][0] == '$')
        {
            result = ft_strrchr(arr[i], '$');
            printf("%s", getenv(result));
        }
        if (arr[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (flg == 1)
        printf("\n");
}
