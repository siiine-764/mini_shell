/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:56:48 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/17 20:17:30 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

char    *get_key(char *str)
{
    char    *key;
    int     j;
    int     k;
    k = 0;
    j = 0;
    while(str[j])
    {
        if (str[j] == '=')
        {
            key = malloc(sizeof(char) * j + 2);
            if (!key)
                return (NULL);
            k = 0;
            while(k <= j)
            {
                key[k] = str[k];
                k++;
            }
            key[k] = '\0';
            return (key);
        }
        j++;
    }
    return (NULL);
}

char    *get_value(char *str)
{
    char    *value;
    int     j;
    int     k;
    int     start;
    int     len;

    k = 0;
    while(str[k])
    {
        if (str[k] == '=')
        {
            // printf("----%s---", &str[k]);
            start = 0;
            len = 0;
            k++;
            j = k;
            while (str[k])
            {
                len++;
                k++;
            }
            // printf("---> len: %d\n", len);
            // printf("---> j: %d\n", j);
            value = malloc(sizeof(char) * (len + 1));
            if (!value)
                return (NULL);
            while (str[j])
            {
                value[start] = str[j];
                start++;
                j++;
            }
            value[start] = '\0';
                // printf("----%s-----\n", value);
                // printf("%s\n", value);
            return (value);
        }
        k++;
    }
    return (NULL);
}

// void    get_env(char **env, t_env   *e)
// {
//     int i;
//     int len;
    
//     e->test = 0;
//     i = 0;
//     len = 0;
//     while (env[len])
//         len++;
//     e->key = malloc(sizeof(char *) * len + 1);
//     e->value = malloc(sizeof(char *) * len);
//     while (env[i])
//     {
//         // printf("----? %s", env[i]);
//         get_key(env[i], e);
//         get_value(env[i]);
//         // add_node(env[i]);
//         e->test++;
//         i++;
//     }
// }


