/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:56:38 by hben-mes          #+#    #+#             */
/*   Updated: 2023/06/13 02:41:46 by mayache-         ###   ########.fr       */
/*   Updated: 2023/06/09 22:08:38 by hben-mes         ###   ########.fr       */
/*   Updated: 2023/06/09 20:17:36 by mayache-         ###   ########.fr       */
/*   Updated: 2023/06/09 21:58:07 by hben-mes         ###   ########.fr       */
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
#include <limits.h>

char **g_env;

struct Node {
  char      *val;
  char      *key;
  struct Node* next;
};

typedef struct s_env
{
    char            **val;
    char            **key;
    int             len_key;
    int             test;
    // struct s_env    *next;
}	t_env;

typedef struct s_add_env
{
    char            **new_env;
}	t_add_env;


/// functions builtins ///
void		pwd(void);
void		cd(char **env, t_env *e);
void		un_set(struct Node* head, char *add_key);
void		ft_ex_port(struct Node* head, char *add_key, char *add_val);
void		echo(char **arr);
void		ex_it(void);
/// end functions builtins ///


struct Node	*createNode(char  *val, char  *key);
void		insertNode(struct Node** head, char  *val, char  *key);
void		displayList(struct Node* head);
void		deleteNode(struct Node** head_ref, const char* key);

/// functions env ///
int			ft_strstartswith(char *s1, char *s2);
int			str_len(char *env);
char		*ft_str_dup(char *s1);
char		*str_join(char *s1, char *s2);
char		**ft_arr_dup(char **origin);
char		*get_key(char *str, t_env *e);
char		*get_value(char *str, t_env *e);
void		get_env(char **env, t_env   *e);
/// end functions env ///






#endif