/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:56:48 by mayache-          #+#    #+#             */
/*   Updated: 2023/06/17 00:51:11 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

void    get_key(char *str, t_env *e)
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
            k = 0;
            while(k <= j)
            {
                key[k] = str[k];
                k++;
            }
            key[k] = '\0';
            e->key[e->test] = ft_str_dup(key);
            e->len_key = k;
            free(key);
        }
        j++;
    }
}

void    get_value(char *str, t_env *e)
{
    char    *value;
    int     j;
    int     k;
    int     len;

    j = 0;
    len = str_len(str);
    k = e->len_key + 1;
    len -= e->len_key + 1;
    value = malloc(sizeof(char) * len + 1);
    while(str[k])
    {
        value[j] = str[k];
        k++;
        j++;
    }
    value[j] = '\0';
    e->value[e->test] = ft_str_dup(value);
    free(value);
}

void    get_env(char **env, t_env   *e)
{
    int i;
    int len;
    
    e->test = 0;
    i = 0;
    len = 0;
    while (env[len])
        len++;
    e->key = malloc(sizeof(char *) * len + 1);
    e->value = malloc(sizeof(char *) * len);
    while (env[i])
    {
        // printf("----? %s", env[i]);
        get_key(env[i], e);
        get_value(env[i], e);
        // add_node(env[i]);
        e->test++;
        i++;
    }
}


