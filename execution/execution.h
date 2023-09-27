/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:56:49 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/26 18:42:19 by mayache-         ###   ########.fr       */
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

# define REDIRECT_OUTPUT 62 //redirect output > = 62
# define REDIRECT_INPUT 60 //redirect input  < = 60
# define REDIRECT_OUTPUT_APPEND 124  //should redirect output in append mode >> = 62 + 62
# define HERE_DOC 120      // redirect  delimite << = 60 + 60
char **g_env;
struct Node {
  char      *val;
  char      *key;
  char      *content;
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

typedef struct s_redir
{
    char    *file;
    int     typ_redir;
    int     cnt_redir;
} t_redir;

typedef struct s_cmd
{
    char    **cmd; //comand 
	char	*flag; // flangs 
    int cnt; // count comnad how much 
    // int fpipe;
    // int rpipe;
    int pipe; // boolean 0 || 1
    int cnt_pipe; // count pipe how much
    char ***arguments; // arguments
    char  **txt; // text 
    t_redir *redir; // directions
} t_cmd;

typedef struct s_path
{
    char    **path;
    int cnt;
}	t_path;

/// functions builtins ///
void		pwd(void);
void        cd(char **env, struct Node* head, t_cmd *my_cmd);
void		un_set(struct Node* head, char *add_key);
void		ft_ex_port(struct Node* head, char *add_key, char *add_val,char **env);
void		e_cho(char **arr, char *flag);
void		ex_it(void);

/// end functions builtins ///

/// functions execution ///
// int	check_builtins(char *cmd);
// void    execute_cmd(char *cmd, struct Node* head, char *add_key, char *add_val);
void    execute(t_cmd *my_cmd, char **env);
void    excute_cpy(t_cmd *my_cmd, char **env, struct Node* head, char *input);
int     run_builtins0(char *input, struct Node* head, char **env, t_cmd *my_cmd);
int     run_builtins1(t_cmd *my_cmd, char **env, char *input, struct Node* head);
int     run_builtins2(t_cmd *my_cmd, char *input, struct Node* head);
int     execute_builtins(char **env, char *input, struct Node* head, t_cmd *my_cmd);
t_path    *get_path(char *path);
void    excute_cmd(t_cmd *my_cmd, t_path *p);
/// end functions execution ///

/// functions pipe ///
void    pi_pe(t_cmd *my_cmd, t_path *p);
void    my_execve(char *file, char *args[], t_path *p);
void    wait_all(int cnt_pipe);

/// end functions pipe ///

/// functions redirect ///
void ft_redir(t_cmd *my_cmd, t_path *p);
void ft_redirect_output(char *file, t_path *p, t_cmd *my_cmd);
void ft_redirect_input(char *file, t_path *p, t_cmd *my_cmd);
void ft_redirect_output_append(char *file, t_path *p, t_cmd *my_cmd);
char *ft_redir_herdoc(t_cmd *my_cmd, char *delimiter);
/// end functions redirect ///

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
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
int	sizew(char const *s, char c, int i);
/// end functions utils ///

#endif