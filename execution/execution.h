/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:56:49 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/20 23:22:24 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// # include "./libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/stat.h>
# include <limits.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

char **g_env;

enum e_node_typ
{
	CMD,
	PIPE,
};

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

typedef struct s_cmd
{
    char    **cmd;
	char	*flag;
    int cnt;
    int fpipe;
    int rpipe;
    char **arguments;
    char  **txt;
} t_cmd;

typedef struct s_path
{
    char    **path;
    int cnt;
}	t_path;

// typedef struct s_ast_node
// {
//   enum e_node_type	type;
//   t_union				*content;
// }	t_ast_node;

/// functions builtins ///
void		pwd(void);
void        cd(char **env, struct Node* head);
void		un_set(struct Node* head, char *add_key);
void		ft_ex_port(struct Node* head, char *add_key, char *add_val,char **env);
void		e_cho(char **arr, char *flag);
void		ex_it(void);
/// end functions builtins ///


/// functions execution ///
// int	check_builtins(char *cmd);
// void    execute_cmd(char *cmd, struct Node* head, char *add_key, char *add_val);
void exect(void);
int execute_cmd(char **env, char *input, struct Node* head, t_cmd *my_cmd);
void    get_path(char *path, t_path *p);
/// end functions execution ///


/// functions env ///
struct Node	*createNode(char  *val, char  *key);
void		insertNode(struct Node** head, char  *val, char  *key);
void		displayList(struct Node* head);
void    displayList_export(struct Node* head);
void		deleteNode(struct Node** head_ref, const char* key);

char		*ft_str_dup(char *s1);
char		**ft_arr_dup(char **origin);
char		*get_key(char *str);
char		*get_value(char *str);
void	create_env(char **env, struct Node** head);
/// end functions env ///


/// functions utils ///
char		*str_join(char *s1, char *s2);
int			str_len(char *env);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int	ft_isnum(char *num);
int	ft_isalpha(int c);
int	ft_strcmp(char *s1, char *s2);
/// end functions utils ///

#endif