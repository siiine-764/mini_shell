/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:54:03 by mayache-          #+#    #+#             */
/*   Updated: 2023/06/17 21:21:50 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

//find val emv

// char    find_val(char *val)
// {
//     int i = 0;
// }

// void start_find_val(char **env)
// {
//     int i = 0;

//     while (env[i])
//     {
//         if ()
//     }
// }
////chdir (change directory)

int ft_strcmp(char *str1, char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

void  cd(char **env, t_env *e)
{
    int i = 0;
    int bl = 0;

    while (env[i])
    {
        // printf("------%s\n", get_key(env[i]));
        if (ft_strcmp(get_key(env[i], e), "HOME=") == 0)
        {
            printf("%s\n", get_value(env[i], e));
            bl = 1;
            chdir(get_value(env[i], e));
        }
        i++;
    }
    if (bl == 0)
        printf("Error");
}
