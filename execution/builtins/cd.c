/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:54:03 by mayache-          #+#    #+#             */
/*   Updated: 2023/06/08 22:43:37 by mayache-         ###   ########.fr       */
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
int main(int ac, char **av) {
    cd(av[1]);
    return 0;
}
