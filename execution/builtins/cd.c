/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:54:03 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/20 22:46:14 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void	create_env(char **env, struct Node** head)
{
	int		i;	

	// env = NULL;
	// env = init_env(env);
	// env->env = tab;
	i = 0;
    // (void)env;
    // (void)head;
    // printf("ddddd");
    while(env[i])
    {
        insertNode(head, get_value(env[i]), get_key(env[i]));
        i++;
    }
	// return (env);
}

void  cd(char **env, struct Node* head)
{
	// char		cwd[1024];
	// char		owd[1024];

    (void)head;
    (void)env;
    // create_env(env, &head);

	// getcwd(owd, sizeof(owd));  

    // printf("%s", getcwd(owd, getcwd(owd, sizeof(owd))));
    // int bl = 0;
    // int i = 0;
    // while (env[i])
    // {
    //     // printf("------%s\n", get_key(env[i]));
    //     if (ft_strcmp(get_key(env[i]), "HOME=") == 0)
    //     {
    //         printf("%s\n", get_value(env[i]));
    //         bl = 1
    char *a = getenv("HOME");
                chdir(a);
                // pwd();
    //     }
    //     i++;
    // }
    // if (bl == 0)
    //     printf("Error");
}
