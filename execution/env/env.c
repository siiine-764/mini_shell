/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:57:27 by mayache-          #+#    #+#             */
/*   Updated: 2023/06/09 20:32:42 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"
void add_node(char *env)
{
    int     i;
    int     j;
    t_env   *e;

    i = 0;
    j = 0;
    // e->next = NULL;
    while (env[i])
    {
        if (env[i] != '=')
        {
            e->value = &env[i];
        }
        else if (env[i] == '=')
        {
            j = i;
            while(env[j])
            {
                e->path = &env[j];
                j++;
            }
            printf("----%s\n", e->path);
        }
        e->next = *env;
        i++;
    }
}

void    get_env(char **env)
{
    int i;

    i = 0;
    printf("ffff");
    while (env[i])
    {
        printf("%d", i);
        add_node(env[i]);
        printf("\n");
        i++;
    }
}

int main(int ac, char **av, char **ev) {

    get_env(ev);
    return 0;
}