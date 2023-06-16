/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:57:27 by mayache-          #+#    #+#             */
/*   Updated: 2023/06/17 00:46:48 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"


//-fsanitize=address

// void add_node(char *env)
// {
//     int     i;
//     int     j;
//     t_env   *e;

//     i = 0;
//     j = 0;
//     // e->next = NULL;
//     while (env[i] != '\0')
//     {
//         // if (env[i] != '=')
//         // {
//             e->value = &env[i];
//             printf("value: %s\n", e->value);
//         // }
//         // else if (env[i] == '=')
//         // {
//         //     j = i;
//         //     while(env[j])
//         //     {
//         //         e->path = &env[j];
//         //         printf("----%s\n", e->path);
//         //         j++;
//         //     }
//         // }
//         // e->next = *env;
//         i++;
//     }
// }


// void    add_env(t_env   *e, char *env)
// {
//     e->test++;
//     char    **dd = malloc(sizeof(char *) * e->test + 1);
//     dd = ft_arr_dup(g_env);
//     free(g_env);
//     int i = 0;
//     while(i < e->test)
//     {
//         dd[i] = str_join(key, value);
//         i++;
//     }
//     // e->value[e->test] = value;
//     // e->key[e->test] = key;
// }

int main(int ac, char **av, char **ev)
{
    t_env   *e = malloc(sizeof(t_env));
        
    (void)ac;
    (void)av;
    get_env(ev, e);
    int    i = 0;
    // printf("---- 1 ---\n");
    while(i < e->test)
    {
        // e->key[i] = join_char_str(e->key[i], '=');
        printf("%s", e->key[i]);
        printf("%s\n", e->value[i]);
        i++;
    }
    // t_add_env *new = NULL;
    // new->new_env = malloc(sizeof(char *) * e->test + 1);
    char    **arr = malloc(sizeof(char *) * e->test + 1);
    char    **g_env = malloc(sizeof(char *) * e->test + 1);
    i = 0;
    while (i < e->test)
    {
        arr[i] = str_join(e->key[i], e->value[i]);
        g_env[i] = ft_str_dup(arr[i]);
        free(arr[i]);
        i++;
    }
    i = 0;
    while (i < e->test)
    {
        printf("%s\n", g_env[i]);
        i++;
    }
    // add_env(e,"test=rrrrr");
    // printf("----%d---\n", e->test);

    // printf("---- 2 ---\n");
    // i = 0;
    // while(i < e->test)
    // {
    //     // printf("%s=", e->key[i]);
    //     // printf("%s\n", e->value[i]);
    //     printf("%s", env[i]);
    //     i++;
    // }
    // char* value = getenv("HOME");
    // if (value != NULL) {
    //     printf("The value of HOME is: %s\n", value);
    // } else {
    //     printf("HOME environment variable is not set.\n");
    // }

    // char* name = "MY_VARIABLE";
    // char* v = "Hello, World!";
    // char* env = malloc(strlen(name) + strlen(v) + 2);
    // sprintf(env, "%s=%s", name, v);
    // if (putenv(env) == 0) {
    //     printf("%s\n", getenv(name));
    //     printf("Environment variable set successfully.\n");
    // } else {
    //     printf("Failed to set environment variable.\n");
    // }
    // free(env);
    // while(1);
    // free(e);
    // free(e->key);
    // free(e->value);
    return 0;
}
