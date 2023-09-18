/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:56:38 by hben-mes          #+#    #+#             */
/*   Updated: 2023/09/18 18:05:38 by mayache-         ###   ########.fr       */
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
#include <fcntl.h>
#include <limits.h>

char **g_env;

#define CMD 1;
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

// typedef struct s_ast_node
// {
//   enum e_node_type	type;
//   t_union				*content;
// }	t_ast_node;

/// functions builtins ///
void		pwd(void);
// void		cd(char **env, t_env *e);
void  cd(char **env, struct Node* head);
void		un_set(struct Node* head, char *add_key);
void		ft_ex_port(struct Node* head, char *add_key, char *add_val);
void		echo(char **arr);
void		ex_it(void);
/// end functions builtins ///


struct Node	*createNode(char  *val, char  *key);
void		insertNode(struct Node** head, char  *val, char  *key);
void		displayList(struct Node* head);
void    displayList_export(struct Node* head);
void		deleteNode(struct Node** head_ref, const char* key);

/// functions env ///
int			ft_strstartswith(char *s1, char *s2);
int			str_len(char *env);
char		*ft_str_dup(char *s1);
char		*str_join(char *s1, char *s2);
char		**ft_arr_dup(char **origin);
char		*get_key(char *str);
char		*get_value(char *str);
void		get_env(char **env, t_env   *e);

/// end functions env ///

void exect(void);
void	create_env(char **env, struct Node** head);
int	ft_strcmp(char *s1, char *s2);
int	ft_isalpha(int c);



#endif