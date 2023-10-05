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
	int		exit_code;
	int		signal_flag;
	int		sig_type;
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

t_tkn	*tkn_initialize(char *data, int typ);
t_lxr		*lxr_initialize(char *ctt);
t_tkn		*tkn_nxt(t_lxr *lxr, t_env *env_list);

t_top_cmd	*ft_execution(char *ctt, t_env *env_list);
t_tkn		*ft_redirection(t_lxr *lxr, t_env *env_list);
t_tkn		*handle_her(t_lxr *lxr, t_env *env_list);

t_env		*ft_getenv(t_env *env_list, char *variable);
t_env		*get_env_list(char **i);
t_frame		open_files(t_tkn_top redirection);

int		fill_temp_stdin(t_comm *comm);
void	exec_node(t_data *data, t_comm *comm, t_frame frame);
bool	heredoc_exist(t_data *data);
int		count_commands_before_heredoc(t_comm *comm);
void	check_before_heredoc_commands(t_data *data, t_info my_info, int i);
void	run_commands_before_heredoc(t_data *data, t_info my_info, int i);
void	exec_commands_before_heredoc(t_data *data);
void	sort_list(t_env **env_list);
void	cd_oldwd(t_env *env_list, t_env *pub_list);
void	cd_home(t_env *env_list, t_env *pub_list);
void	ft_cd(t_env *env_list, t_env *pub_list, char *path);
bool	run_cd(t_data data, t_comm *comm);
bool	check_redirection(t_data *data, t_comm *comm);
char	*join_for_echo(char **str, char flag);
void	check_echo(char *str, char flag, int fd, t_frame frame);
void	ft_echo(t_comm *comm, char *str, char flag, t_frame frame);
int		check_echo_flag(char *str);
char	*check_for_space( int i, char **str, char *res);
bool	exec_echo(t_data data, t_comm *comm, t_frame frame);
void	ft_env(t_data data, t_comm *comm, t_frame frame);
bool	run_env(t_data data, t_comm *comm, t_frame frame);
int		is_properly_named(char *str);
void	ft_setenv(t_env **env_list, char *variable, char *value);
void	check_command_error(t_data *data, t_comm *comm);
void	check_command_error_2(t_data *data, t_comm *comm);
void	check_path(t_data *data, t_comm *comm);
void	check_files(t_tkn_top redirection);
void	set_exit_code_inside_pipe(t_data *data, t_comm *comm);
int		get_len(t_comm *comm);
int		check_built_in_commands(t_data *data, t_comm *comm, t_frame frame);
void	ft_execute(t_comm *comm, t_data *data, t_frame frame);
void	close_pipe(int *fd);
char	*get_path(t_env *env_list, char *c);
void	ft_error(char *i, char *l, int exit);
void	exec_command( t_data *data, t_comm *comm,
		t_frame frame, char *p_comm);
void	run_excutable(t_comm *comm, t_data *data, t_frame frame);
void	check_cmd(t_comm *comm, t_data *data, t_frame frame);
void	ft_exit(char flag, char *var);
bool	add_variable(t_data *data, t_comm *comm, char **s, int j);
void	add_non_variable(t_data *data, t_comm *comm, char **s, int j);
void	show_export_error(t_comm *comm, int j, int *flag);
void	add_properly_named_word( t_data *data, t_comm *comm, int j);
int		is_variable(char *str);
void	ft_export(t_comm *comm, t_env *env, char *var);
void	show_export_list(t_comm *comm, t_data data, t_frame frame);
void	add_unexisted_variable(t_data *data, t_comm*comm,
		char **s, int i);
void	add_existed_variable(t_data *data, t_comm *comm, 
		char **s, int i);
bool	run_export(t_comm *comm, t_data *data, t_frame frame);
bool	is_number(char *str);
bool	run_exit(t_data data, t_comm *comm);
void	check_export_error(t_data *data, t_comm *comm);
void	check_cd_errors(t_data *data, t_comm *comm);
void	ft_pwd(t_data data, t_comm *comm, t_frame frame);
bool	run_pwd(t_data data, t_comm *comm, t_frame frame);
void	exec_first_command_before_heredoc(t_data *data, t_info my_info);
void	exec_last_command_before_heredoc(t_data *data, t_info my_info);
void	exec_other_command_before_heredoc(t_data *data, t_info my_info);
void	open_heredoc(t_comm **comm);
bool	heredoc_outside_pipe(t_data *data, t_comm *comm);
void	check_out_files(int *fd_out, int *output);
void	check_in_files(int *stdin_temp, int *fd_in);
int		heredoc_return(int output, t_frame frame);
void	read_for_heredoc(t_comm *comm, int fd_in);
void	exec_first_node(t_data *data, t_info my_info);
void	exec_last_node(t_data *data, t_info my_info);
void	exec_other_node(t_data *data, t_info my_info);
void	wait_for_child(int *ids, int fd_temp, int i);
void	check_commands_order(t_data *data, t_info *my_info);
void	exec_after_heredoc(t_info *my_info, t_data *data, int *p);
void	run_heredoc(t_data *data, int *fd_heredoc, t_info my_info);
void	loop_through_nodes(t_data *data, t_info my_info);
bool	check_heredoc(t_comm *comm);
void	ft_pipe(t_data *data);
int		ft_strcmp(char *str, char *p);
char	*get_promt(void);
void	init_contex(t_frame *frame);
void	walk_to_heredoc(t_comm **comm);
int		open_input_files(t_tkn_top redirection);
int		open_trunc_mode_files(t_tkn_top redirection);
int		open_append_mode_files(t_tkn_top redirection);
void	ft_redirect_output_append_mode(t_comm *comm, t_data *data);
void	ft_redirect_output_trunc_mode(t_comm *comm, t_data *data);
void	redirect_input(t_comm *comm, t_data *data);
void	exec_herdoc_command(t_comm *comm, t_data *data, t_frame frame);
int		ft_heredoc(t_data *data, t_comm *comm, t_frame frame);
void	delete_body(t_info *data);
void	ft_unset(t_env **env_list, char *del);
bool	run_unset(t_data *data, t_comm *comm);
char	*find_env(t_env *env_list, char *name);
void	ft_move(t_lxr	*lxr);
int		exit_code(void);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
int		ft_isalnum(int c);
int		ft_isdigit(int digit);
void	space_skip(t_lxr	*lxr);
char	*get_data(t_lxr *lxr, t_env *env_list, int l);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*join_free(char *s, char *t);
char	*join_str(t_lxr *lxr, t_env *env_list, int l);
int		syntax_handle(char *data, t_tkn *tk, t_top_cmd *top);
void		ft_initialize(t_top_cmd *top);
int			cmd_add(t_top_cmd *top, t_lxr *lxr, t_env *env_list);
int			node_load(t_comm *red, t_lxr *lxr, t_env *env_list, t_top_cmd *top);
char		**ft_dup(char **av, char *data, int i);
int			token_check(t_tkn *tkn, t_comm *red, t_top_cmd *top, int *i);
void		all_free(t_top_cmd *top);
void		put_exit(int i);
int			rederiction_handle(t_comm *red, t_tkn *tkn, t_top_cmd *top);
int			aft_dollar_check(t_lxr *lxr);
char		*aft_dollar(t_lxr *lxr, t_env *env_list);
char		*unquoted_str(t_lxr *lxr, t_env *env_list, int l);
char		*str_collect(t_lxr *lxr, t_env *env_list, char cmd, int l);
char		*get_var(t_lxr *lxr, t_env *env_list);
char		*ft_strjoin(char *s1, char *s2);

#endif