/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:56:38 by hben-mes          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/09 20:17:36 by mayache-         ###   ########.fr       */
=======
/*   Updated: 2023/06/09 21:58:07 by hben-mes         ###   ########.fr       */
>>>>>>> 37ba95c3dc119cff709e4b958ab168c265c3f0ed
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
    char    *value;
    char    *path;
    int     next;
}	t_env;










#endif