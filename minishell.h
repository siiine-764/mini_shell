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


#include "./libft/libft.h"
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
	char	**p_comm;
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

t_tkn		*tkn_initialize(int typ, char *val);
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
int			check_built_in_commands(t_data *data, t_comm *comm, t_frame frame);
char		*join_for_echo(char **str, char flag);
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
void	ft_redirect_output_trunc_mode(t_comm *comm, t_data *data);
void		redirect_input(t_comm *comm, t_data *data);
void		exec_last_node(t_data *data, t_info my_info);
void		exec_first_node(t_data *data, t_info my_info);
void		exec_other_node(t_data *data, t_info my_info);
void		ft_export(t_comm *comm, t_env *env, char *var);
void		exec_first_command_before_heredoc(t_data *data, t_info my_info);
void		exec_last_command_before_heredoc(t_data *data, t_info my_info);
void		exec_other_command_before_heredoc(t_data *data, t_info my_info);
void	add_properly_named_word(t_comm *comm, t_data *data, int j);
void	show_export_error( int *flag, int j, t_comm *comm);
void		ft_exit(char *var, char flag);
void	add_existed_variable(t_comm *comm, t_data *data, 
			char **s, int i);
void	add_non_variable(t_comm *comm, t_data *data, char **s, int j);
void		add_unexisted_variable(t_comm*comm, t_data *data,
		char **s, int i);
void	exec_command(t_comm *comm, t_data *data,
		t_frame frame, char *p_comm);
void	set_exit_code_inside_pipe(t_data *data, t_comm *comm);
void	init_contex(t_frame *frame);
void	show_export_list(t_comm *comm, t_data data, t_frame frame);
void	ft_cd(t_env *env_list, t_env *pub_list, char *path);
void	cd_oldwd(t_env *env_list, t_env *pub_list);
void	cd_home(t_env *env_list, t_env *pub_list);
int			cmd_add(t_top_cmd *top, t_lxr *lxr, t_env *env_list);
int    get_parts(char const *s, char c);
int			aft_dollar_check(t_lxr *lxr);
int			syntax_handle(char *val, t_tkn *t, t_top_cmd *top);
int		rederiction_handle(t_comm *red, t_tkn *tkn, t_top_cmd *top);
int		pipe_check(t_lxr *lxr, t_tkn *tkn, int l, t_top_cmd *top);
int		token_check(t_tkn *tkn, t_comm *red, int *i, t_top_cmd *top);
int	check_built_in_commands(t_data *data, t_comm *comm, t_frame frame);
int	ft_strcmp(char *str, char *p);
int	get_len(t_comm *comm);
int	get_exit_code(void);
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
int		node_load(t_comm *red, t_lxr *lxr, t_env *env_list, t_top_cmd *top);
char	*find_env(t_env *env_list, char *name);
char	*prime_str_collect(t_lxr *lxr, t_env *env_list, char cmd, int l);
char	*join_free(char *s, char *t);
char	*join_str(t_lxr *lxr, t_env *env_list, int l);
char	*aft_dollar(t_lxr *lxr, t_env *env_list);
char	*str_collect(t_lxr *lxr, t_env *env_list, char cmd, int l);
char		*get_data(t_lxr *lxr, t_env *env_list, int l);
char		*str_put(t_lxr *lxr, t_env *env_list, int l);
char		*unquoted_str(t_lxr *lxr, t_env *env_list, int l);
char		**ft_dup(char **av, char *val, int i);
bool	exec_echo(t_data data, t_comm *comm, t_frame frame);
bool	add_variable(t_comm *comm, t_data *data, char **s, int j);
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
void	check_out_files(int *fd_out, int *f_output);


#endif