/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:54:03 by mayache-          #+#    #+#             */
/*   Updated: 2023/06/11 01:46:58 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"


////chdir (change directory)
void  cd(char *av)
{
    if(chdir(av) == 0) {
        printf("Directory changed successfully. \n");
    }
    else {
        perror("Error");
    }
} 
// int main(int ac, char **av, char **ev) {
//     while (*ev)
//     {
//         printf("%s\n", *ev);
//         ev++;
//     }
//     return 0;
// }
