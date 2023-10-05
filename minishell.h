/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_copy.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:30:11 by hben-mes          #+#    #+#             */
/*   Updated: 2023/10/03 23:30:11 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


typedef struct s_env
{
	char			*ctt;
	struct s_env	*nxt;
}t_env;

typedef enum typ
{
	T_WORD,
	T_IN,
	T_OUT,
	T_HERDOC,
	T_APPEND,
	T_PIPE
}	t_typ;

typedef struct data
{
	pid_t	pid;
	int		e;
	int		signal_flag;
	int		sig_typ;
}t_data_g;

typedef struct TKN
{
	t_typ			tkn;
	char			*val;
	struct TKN		*nxt;
}t_tkn;

typedef struct t_tkn_top
{
	t_tkn	*fst_tkn;
}t_tkn_top;

typedef struct parsing
{
	char					**flags;
	struct parsing			*nxt_comm;
	t_tkn_top				*redirection;
	t_tkn_top				*heredoc;
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

typedef struct s_docs
{
	int	in;
	int	trunc;
	int	append;
}t_docs;

typedef struct s_p_data
{
	char	*path;
	char	*temp;
	char	**comm_path;
	int		i;
}t_p_data;

typedef struct s_my_data
{
	char	new_wd[PATH_MAX];
	char	buff[PATH_MAX];
	char	*t_path;
	char	**temp;
	t_env	*previous_wd;
	int		i;
}t_my_data;

typedef struct s_data
{
	t_env		*env_list;
	t_env		*pub_list;
	char		**env;
	t_top_cmd	*top;
	int			comm_num;
	t_comm		*comm;
}t_data;

typedef struct s_frame
{
	int		fd_in;
	int		fd_out;
	int		heredoc_docs;
}t_frame;

typedef struct s_info
{
	t_env		*fst;
	t_env		*sec;
	t_env		*temp;
	char		**command;
	int			*ids;
	int			i;
	int			id;
	int			size;
	int			temp_fd;
	t_frame		frame;
	int			fd[2];
}t_info;

extern t_data_g	g_global_data;

t_tkn		*tkn_initialize(char *data, int typ);
t_lxr		*lxr_initialize(char *ctt);
t_tkn		*tkn_nxt(t_lxr *lxr, t_env *env_list);

t_top_cmd	*ft_execution(char *ctt, t_env *env_list);
t_tkn		*ft_redirection(t_lxr *lxr, t_env *env_list);
t_tkn		*handle_her(t_lxr *lxr, t_env *env_list);

t_env		*ft_getenv(t_env *env_list, char *variable);
t_env		*get_env_list(char **i);
t_frame		open_files(t_tkn_top redirection);

int			fill_temp_stdin(t_comm *comm);
void		exec_node(t_data *data, t_comm *comm, t_frame frame);
int			check_built_in_commands(t_data *data, t_comm *comm, t_frame frame);
char		*join_for_echo(char **str, char flag);
void		check_commands_order(t_data *data, t_info *my_info);
void		all_free(t_top_cmd *top);
int			heredoc_return(int f_output, t_frame frame);
void		walk_to_heredoc(t_comm **comm);
void		close_pipe(int *fd);
void		check_in_files(int *stdin_temp, int *fd_in);
void		redirection_add(t_tkn_top *top, t_tkn *t);
void		ft_initialize(t_top_cmd *top);
void		node_add(t_top_cmd *top, t_comm *comm);
void		ft_move(t_lxr	*lxr);
void		space_skip(t_lxr	*lxr);
void		check_export_error(t_data *data, t_comm *comm);
void		check_cd_errors(t_data *data, t_comm *comm);
void		set_exit_code_inside_pipe(t_data *data, t_comm *comm);
void		read_for_heredoc(t_comm *comm, int fd_in);
void		open_heredoc(t_comm **comm);
void		free_list(t_env *env);
void		ft_error(char *i, char *l, int exit);
void		wait_for_child(int *ids, int temp_fd, int i);
void		exec_commands_before_heredoc(t_data *data);
void		check_cmd(t_comm *comm, t_data *data, t_frame frame);
void		exec_node(t_data *data, t_comm *comm, t_frame frame);
void		ft_execute(t_comm *comm, t_data *data, t_frame frame);
void		ft_pipe(t_data *data);
void		ft_env(t_data data, t_comm *comm, t_frame frame);
void		free_2d(char **a);
void		sig_handler(int sig);
void		ft_pwd(t_data data, t_comm *comm, t_frame frame);
void		sort_list(t_env **env_list);
void		ft_unset(t_env **env_list, char *del);
void		ft_setenv(t_env **env_list, char *variable, char *value);
void		set_exit_code(int i);
void		ft_redirect_output_append_mode(t_comm *comm, t_data *data);
void		ft_redirect_output_trunc_mode(t_comm *comm, t_data *data);
void		redirect_input(t_comm *comm, t_data *data);
void		exec_last_node(t_data *data, t_info my_info);
void		exec_first_node(t_data *data, t_info my_info);
void		exec_other_node(t_data *data, t_info my_info);
void		ft_export(t_comm *comm, t_env *env, char *var);
void		exec_first_command_before_heredoc(t_data *data, t_info my_info);
void		exec_last_command_before_heredoc(t_data *data, t_info my_info);
void		exec_other_command_before_heredoc(t_data *data, t_info my_info);
void		add_properly_named_word( t_data *data, t_comm *comm, int j);
void		show_export_error(t_comm *comm, int j, int *flag);
void		ft_exit(char flag, char *var);
void		add_existed_variable(t_data *data, t_comm *comm, 
		char **s, int i);
void		add_non_variable(t_data *data, t_comm *comm, char **s, int j);
void		add_unexisted_variable(t_data *data, t_comm*comm,
		char **s, int i);
void	exec_command( t_data *data, t_comm *comm,
		t_frame frame, char *p_comm);
void	set_exit_code_inside_pipe(t_data *data, t_comm *comm);
void	init_contex(t_frame *frame);
void	show_export_list(t_comm *comm, t_data data, t_frame frame);
void	ft_cd(t_env *env_list, t_env *pub_list, char *path);
void	cd_oldwd(t_env *env_list, t_env *pub_list);
void	cd_home(t_env *env_list, t_env *pub_list);

///////////////////////////////////////////////////////////////////////////////////////
int			check_built_in_commands(t_vars *vars,
				t_command *command, t_contex contex);
int			ft_add_commande(t_head_c *head, t_lexer *lexer, t_list *env_list);
int			ft_strcmp(char *s, char *str);
int			get_len(t_command *command);
int			cut_exit_code(char *arg);
int			get_exit_code(void);
int			get_parts(char	*s, char c);
int			is_variable(char *s);
int			ft_check_after_dollar(t_lexer *lexer);
int			check_echo_flag(char *s);
int			is_properly_named(char *s);
int			ft_heredoc(t_vars *vars, t_command *command, t_contex contex);
int			count_commands_before_heredoc(t_command *command);
int			get_signal_flag(void);
int			ft_syntax(char *value, t_token *t, t_head_c *head);
int			ft_rederictions(t_command *re, t_token *token, t_head_c *head);
int			ft_check_pipe(t_lexer *lexer, t_token *token,
				int k, t_head_c *head);
int			ft_check_token(t_token *token, t_command *re,
				int *i, t_head_c *head);
int			ft_fill_node(t_command *re, t_lexer *lexer,
				t_list *env_list, t_head_c *head);
bool		run_pwd(t_vars vars, t_command *command, t_contex contex);
char		*get_promt(void);
char		*get_path(t_list *env_list, char *cmd);
char		*ft_get_env_val(t_list *env_list, char *var_name);
char		*ft_help_collect_str(t_lexer *lexer, \
			t_list *env_list, char c, int h);
char		*ft_join_and_clean(char *str, char *s);
char		*ft_str_for_join(t_lexer *lexer, t_list *env_list, int h);
char		*ft_after_dollar(t_lexer *lexer, t_list *env_list);
char		*ft_collect_string(t_lexer *lexer, char c, t_list *env_list, int h);
char		*ft_get_value(t_lexer *lexer, t_list *env_list, int h);
char		*ft_get_str(t_lexer *lexer, t_list *env_list, int h);
char		*ft_get_str_without_quote(t_lexer *lexer, t_list *env_list, int h);
char		**ft_replace(char **av, int i, char *value);
char		*join_for_echo(char **s, char flag);
char		*check_for_space(char **s, char *result, int i);
char		*join_for_echo(char **s, char flag);

bool		is_number(char *s);
bool		exec_echo(t_vars vars, t_command *command, t_contex contex);
bool		add_variable(t_command *command, t_vars *vars, char **temp, int i);
bool		check_redirection(t_vars *vars, t_command *command);
bool		heredoc_outside_pipe(t_vars *vars, t_command *command);
bool		run_exit(t_vars vars, t_command *command);
bool		run_cd(t_vars vars, t_command *command);
bool		run_env(t_vars vars, t_command *command, t_contex contex);
bool		run_unset(t_vars *vars, t_command *command);
void		ft_echo(t_command *command, char *s, char flag, t_contex contex);
bool		run_export(t_command *command, t_vars *vars, t_contex contex);
void		show_export_list(t_command *command, t_vars vars, t_contex contex);

#endif