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
// int			check_built_in_commands(t_data *data, t_comm *comm, t_frame frame)
// char		*join_for_echo(char **str, char flag)
///////////////////////////////////////////////////////////
void	check_commands_order(t_data *data, t_info *my_info);
void		ft_free_all(t_head_c *head);
int			heredoc_return(int outfile, t_contex contex);
void		check_out_files(int *out_file, int *fd_out);
void		walk_to_heredoc(t_command **command);
void		close_pipe(int *fd);
void		check_in_files(int *fd_in, int *temp_stdin);
void		ft_add_red(t_token_head *head, t_token *t);
void		ft_init_head(t_head_c *head);
void		ft_add_node(t_head_c *head, t_command *commande);
void		ft_advance(t_lexer	*lexer);
void		ft_skip_spaces(t_lexer	*lexer);
void		check_export_error(t_vars *vars, t_command *command);
void		check_cd_errors(t_vars *vars, t_command *command);
void		set_exit_code_inside_pipe(t_vars *vars, t_command *command);
void		read_for_heredoc(t_command *command, int fd_in);
void		open_heredoc(t_command **command);
void		set_signal_flag(int num);
void		free_list(t_list *list);
void		ft_error(char *arg, char *msg, int exit_code);
void		wait_for_child(int *ids, int i, int temp_fd);
void		exec_commands_before_heredoc(t_vars *vars);
void		check_cmd(t_command *command, t_vars *vars, t_contex contex);
void		exec_node(t_vars *vars, t_command *command, t_contex contex);
void		ft_execute(t_command *command, t_vars *vars, t_contex contex);
void		ft_pipe(t_vars *vars);
void		ft_env(t_vars vars, t_command *command, t_contex contex);
void		free_2d_array(char **a);
void		sig_handler(int sig);
void		ft_pwd(t_vars vars, t_command *command, t_contex contex);
void		sort_list(t_list **env_list);
void		ft_unset(t_list **env_list, char *to_delete);
void		ft_setenv(t_list **env_list, char *var_name, char *var_val);
void		set_exit_code(int num);
void		ft_redirect_output_append_mode(t_command *command, t_vars *vars);
void		ft_redirect_output_trunc_mode(t_vars *vars, t_command *command);
void		redirect_input(t_vars *vars, t_command *command);
void		exec_last_node(t_vars *vars, t_norm data);
void		exec_first_node(t_vars *vars, t_norm data);
void		exec_other_node(t_vars *vars, t_norm data);
void		ft_export(t_command *command, t_list *env, char *arg);
void		exec_first_command_before_heredoc(t_vars *vars, t_norm data);
void		exec_last_command_before_heredoc(t_vars *vars, t_norm data);
void		exec_other_command_before_heredoc(t_vars *vars, t_norm data);
void		add_properly_named_word(t_command *command, t_vars *vars, int i);
void		show_export_error(int *flag, int i, t_command *command);
void		ft_exit(char *arg, char flag);
void		add_existed_variable(t_command *command, t_vars *vars,
				int i, char **temp);
void		add_non_variable(t_command *command,
				t_vars *vars, char **temp, int i);
void		add_unexisted_variable(t_command *command, t_vars *vars,
				char **temp, int i);
void		exec_command(t_command *command, t_vars *vars,
				t_contex contex, char *command_path);
void		set_exit_code_inside_pipe(t_vars *vars, t_command *command);
void		init_contex(t_contex *contex);
void		show_export_list(t_command *command, t_vars vars, t_contex contex);
void		cd_oldwd(t_list *env_list, t_list *export_list);
void		cd_home(t_list *env_list, t_list *export_list);
void		ft_cd(char *path, t_list *env_list, t_list *export_list);
///////////////////////////////////////////////////////////////////////////////////////

// int			ft_add_commande(t_head_c *head, t_lexer *lexer, t_list *env_list);
// int			cut_exit_code(char *arg);
// int			get_parts(char	*s, char c);
// int			ft_check_after_dollar(t_lexer *lexer);
// int			get_signal_flag(void);
// int			ft_syntax(char *value, t_token *t, t_head_c *head);
// int			ft_rederictions(t_command *re, t_token *token, t_head_c *head);
// int			ft_check_pipe(t_lexer *lexer, t_token *token,
// 				int k, t_head_c *head);
// int			ft_check_token(t_token *token, t_command *re,
// 				int *i, t_head_c *head);

int	check_built_in_commands(t_data *data, t_comm *comm, t_frame frame);
int	ft_strcmp(char *str, char *p);
int	get_len(t_comm *comm);
int			get_exit_code(void);
int	is_variable(char *str);
int	check_echo_flag(char *str);
int			is_properly_named(char *str);
int	ft_heredoc(t_data *data, t_comm *comm, t_frame frame);
int	count_commands_before_heredoc(t_comm *comm);
bool	run_pwd(t_data data, t_comm *comm, t_frame frame);
char		*get_promt(void);
char	*get_path(t_env *env_list, char *command);
char	*join_for_echo(char **str, char flag);
char	*check_for_space( int i, char **str, char *res);
bool	is_number(char *str);

// int			ft_fill_node(t_command *re, t_lexer *lexer,
// t_list *env_list, t_head_c *head);
// char		*ft_get_env_val(t_list *env_list, char *var_name);
// char		*ft_help_collect_str(t_lexer *lexer, \
// 			t_list *env_list, char c, int h);
// char		*ft_join_and_clean(char *str, char *s);
// char		*ft_str_for_join(t_lexer *lexer, t_list *env_list, int h);
// char		*ft_after_dollar(t_lexer *lexer, t_list *env_list);
// char		*ft_collect_string(t_lexer *lexer, char c, t_list *env_list, int h);



// char		*ft_get_value(t_lexer *lexer, t_list *env_list, int h);
// char		*ft_get_str(t_lexer *lexer, t_list *env_list, int h);
// char		*ft_get_str_without_quote(t_lexer *lexer, t_list *env_list, int h);
// char		**ft_replace(char **av, int i, char *value);


bool	exec_echo(t_data data, t_comm *comm, t_frame frame);
bool	add_variable(t_data *data, t_comm *comm, char **s, int j);
bool	check_redirection(t_data *data, t_comm *comm);
bool	heredoc_outside_pipe(t_data *data, t_comm *comm);
bool	run_exit(t_data data, t_comm *comm);
bool	run_cd(t_data data, t_comm *comm);
bool	run_env(t_data data, t_comm *comm, t_frame frame);
bool	run_env(t_data data, t_comm *comm, t_frame frame);
bool	run_unset(t_data *data, t_comm *comm);
void	ft_echo(t_comm *comm, char *str, char flag, t_frame frame);
bool	run_export(t_comm *comm, t_data *data, t_frame frame);
void	show_export_list(t_comm *comm, t_data data, t_frame frame);

#endif