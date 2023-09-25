/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:23:21 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/25 22:41:15 by mayache-         ###   ########.fr       */
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

void    e_cho(char **arr, char *flag)
{
    int i;
    int flg;
    
    flg = 0;
    i = 1;
    if (check_flag_n(flag) == 1)
    {
        flg = 1;
    }

    while (arr[i])
    {
        printf("%s", arr[i]);
        if (arr[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (flg == 1)
        printf("\n");
}

// int main(int ac, char **av)
// {
//     char *arr[] = {"echo", av[1], av[2], NULL};
//     echo(arr);
// }
