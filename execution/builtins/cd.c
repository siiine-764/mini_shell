/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:54:03 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/01 13:13:40 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"


void	cd_home(struct Node* head, char **env)
{
    (void)head;
    (void)env;

    char *a = getenv("HOME");
    if (a == NULL)
    {
        perror("cd :HOME NOT FOUND");
        return ;
    }
    else
    {
        ft_ex_port(head, "PWD", a, env);
        printf("im here\n");
    }
    chdir(a);
}

void  cd(char **env, struct Node* head, t_cmd *my_cmd)
{
    (void)head;
    (void)env;
    if (ft_strcmp(my_cmd->arguments[0][1], "-") == 0)
    {
        printf("-\n");
    }
    else if (ft_strcmp(my_cmd->arguments[0][1], "~") == 0)
	{
        printf("~\n");
		cd_home(head, env);
	}
    else if (ft_strcmp(my_cmd->arguments[0][1], "..") == 0)
    {
        char *str1 = "OLDPWD";
        ft_ex_port(head, str1, getenv("PWD"), env);
        chdir("..");
        return ;
    }
    else if (ft_strcmp(my_cmd->arguments[0][1], ".") == 0)
    {
        return ;
    }
    else
    {
        printf("cd simple\n");
        cd_home(head, env);
    }
}
