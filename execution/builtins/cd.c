/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:54:03 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/21 18:35:12 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void  cd(char **env, struct Node* head, t_cmd *my_cmd)
{

    (void)head;
    (void)env;
    char *a = getenv("HOME");

    // printf("%s\n", a);
    // char *s= "..";
    // int b = chdir(s);
    // char *pwd = getenv("PWD");
    // printf("%s\n", pwd);
    // char *str = str_join("OLDPwD=", getenv("PWD"));
    // printf("-- %s\n", my_cmd->arguments[0][1]);
    if (ft_strcmp(my_cmd->arguments[0][1], "..") == 0)
    {
        char *str1 = "OLDPWD";
        chdir("..");
        ft_ex_port(head, str1, getenv("PWD"), env);
        return ;
    }
    else if (ft_strcmp(my_cmd->arguments[0][1], ".") == 0)
    {
        return ;
    }
    // ft_ex_port(head, str1, getenv("PWD"), env);
    // printf("str :%s\n", str);
    // printf("---%d\n", b);
    chdir(a);

}
