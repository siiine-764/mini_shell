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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
char **g_env;

#endif