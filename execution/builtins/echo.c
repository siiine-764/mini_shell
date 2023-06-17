/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:23:21 by mayache-          #+#    #+#             */
/*   Updated: 2023/06/11 01:47:07 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

void    echo(char **arr)
{
    int i;
    int flag;

    flag = 0;
    i = 1;
    if (strcmp(arr[i], "-n") == 0)
    {
        flag = 1;
        i++;
    }
    while (arr[i])
    {
        printf("%s", arr[i]);
        if (arr[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (!flag)
        printf("\n");
}

// int main(int ac, char **av)
// {
//     char *arr[] = {"echo", av[1], av[2], NULL};
//     echo(arr);
// }