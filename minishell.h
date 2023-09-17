

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
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
# define PERMISSION_DENIED 126
# define COMMAND_NOT_FOUND 127
# define SUCCESS 0
# define CNTRL_C 130
# define CNTRL_BACKSLASH 131
# define SYNTAX_ERROR_EXIT 258

typedef enum typ
{
	T_WORD,
	T_IN,
	T_OUT,
	T_HERDOC,
	T_APPEND,
	T_PIPE
}	t_typ;

typedef struct TKN
{
	t_typ			tkn;
	char			*data;
	struct TKN	*nxt;
}t_tkn;

typedef struct t_tkn_top
{
	t_tkn	*fst_tkn;
}t_tkn_top;

typedef struct minishellpars
{
	char					**flags;
	struct minishellpars	*nxt_comm;
	t_tkn_top			*redirection;
	t_tkn_top			*heredoc;
}t_comm;

typedef struct top
{
	int			size;
	t_comm	*fst_cmd;
}t_top_cmd;

typedef struct lxr
{
	char	*ctt;
	char	cmd;
	size_t	i;
}t_lxr;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

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