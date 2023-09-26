#ifndef MINISHELL_H
# define MINISHELL_H

// header execution //
#include "./execution/execution.h"
// end header execution //

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
# define PERMISSION_DENIED 126
# define COMMAND_NOT_FOUND 127
# define SUCCESS 0
# define CNTRL_C 130
# define CNTRL_BACKSLASH 131
# define SYNTAX_ERROR_EXIT 258

char *g_global_vars;
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

char	*find_env(t_env *env_list, char *name);
void	ft_move(t_lxr	*lxr);
int	exit_code(void);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
int	ft_isalnum(int c);
int	ft_isdigit(int digit);
void	space_skip(t_lxr	*lxr);
t_tkn	*tkn_initialize(char *data, int typ);
char	*get_data(t_lxr *lxr, t_env *env_list, int l);
int	ft_strncmp(const char *str1, const char *str2, size_t n);
t_tkn	*handle_her(t_lxr *lxr, t_env *env_list);
t_tkn	*ft_redirection(t_lxr *lxr, t_env *env_list);
char	*join_free(char *s, char *t);
char	*join_str(t_lxr *lxr, t_env *env_list, int l);
int	syntax_handle(char *data, t_tkn *tk, t_top_cmd *top);
void	ft_initialize(t_top_cmd *top);
t_top_cmd	*ft_execution(char *ctt, t_env *env_list);
t_tkn	*tkn_nxt(t_lxr *lxr, t_env *env_list);
int	cmd_add(t_top_cmd *top, t_lxr *lxr, t_env *env_list);
int	node_load(t_comm *red, t_lxr *lxr, t_env *env_list, t_top_cmd *top);
t_lxr	*lxr_initialize(char *ctt);
char	**ft_dup(char **av, char *data, int i);
int	token_check(t_tkn *tkn, t_comm *red, t_top_cmd *top, int *i);
void	all_free(t_top_cmd *top);
void	put_exit(int i);
int	rederiction_handle(t_comm *red, t_tkn *tkn, t_top_cmd *top);
int	aft_dollar_check(t_lxr *lxr);
char	*aft_dollar(t_lxr *lxr, t_env *env_list);
char	*unquoted_str(t_lxr *lxr, t_env *env_list, int l);
char	*str_collect(t_lxr *lxr, t_env *env_list, char cmd, int l);
char	*get_var(t_lxr *lxr, t_env *env_list);
char	*ft_strjoin(char *s1, char *s2);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif