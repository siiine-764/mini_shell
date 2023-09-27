/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:54:03 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/26 23:38:26 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int cdDotDot()
{
    if (chdir("..") == 0)
    {
        return 0;
    } else
    {
        perror("cd ..");
        return -1;
    }
}

int cdDot() {
    return 0;
}
//cd ..
// cd .
// cd


void  cd(char **env, struct Node* head, char *input)
{

    (void)head;
    (void)env;
    (void)input;
    // create_env(env, &head);
    // if (ft_strcmp(input, ".."))
    // {
    //     getenv("OLDPWD");
    // }
    char *a = getenv("HOME");
    chdir(a);

}
