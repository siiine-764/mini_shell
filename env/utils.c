/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:56:48 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/23 21:00:02 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

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
            start = 0;
            len = 0;
            k++;
            j = k;
            while (str[k])
            {
                len++;
                k++;
            }
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
            return (value);
        }
        k++;
    }
    return (NULL);
}



