/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:23:21 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/23 17:09:27 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void    e_cho(char **arr, char *flag)
{
    (void)arr;
    (void)flag;
    int i;
    int flg;
    
    flg = 0;
    i = 1;
    if (ft_strcmp(flag, "-n") == 0)
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
