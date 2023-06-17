/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:56:38 by hben-mes          #+#    #+#             */
/*   Updated: 2023/06/13 02:41:46 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

char **g_env;
typedef struct s_env
{
    char            **value;
    char            **key;
    int             len_key;
    int             test;
    // struct s_env    *next;
}	t_env;

typedef struct s_add_env
{
    char            **new_env;
}	t_add_env;

/// functions env ///
int		str_len(char *env);
char	*ft_str_dup(char *s1);
char	*str_join(char *s1, char *s2);
char    **ft_arr_dup(char **origin);
void	get_key(char *str, t_env *e);
void	get_value(char *str, t_env *e);
void	get_env(char **env, t_env   *e);
/// end functions env ///









#endif