/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 04:36:21 by hben-mes          #+#    #+#             */
/*   Updated: 2023/10/12 04:45:48 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
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
}					t_typ;

typedef struct data
{
	pid_t			pid;
	int				e;
	int				signal_flag;
	int				sig_typ;
}					t_data_g;
t_data_g			g_global_data;

typedef struct TKN
{
	t_typ			tkn;
	char			*val;
	struct TKN		*nxt;
}					t_tkn;

typedef struct t_tkn_top
{
	t_tkn			*fst_tkn;
}					t_tkn_top;

typedef struct parsing
{
	char			**flags;
	struct parsing	*nxt_comm;
	t_tkn_top		*redirection;
	t_tkn_top		*heredoc;
}					t_comm;

typedef struct top
{
	int				size;
	t_comm			*fst_cmd;
}					t_top_cmd;

typedef struct lxr
{
	char			*ctt;
	char			cmd;
	size_t			i;
}					t_lxr;

typedef struct s_docs
{
	int				in;
	int				trunc;
	int				append;
}					t_docs;

typedef struct s_p_data
{
	char			*path;
	char			*temp;
	char			**p_comm;
	int				i;
}					t_p_data;

typedef struct s_data
{
	t_env			*env_list;
	t_env			*pub_list;
	char			**env;
	t_top_cmd		*top;
	int				comm_num;
	t_comm			*comm;
}					t_data;

typedef struct s_frame
{
	int				fd_in;
	int				fd_out;
	int				heredoc_docs;
}					t_frame;

typedef struct s_info
{
	t_env			*fst;
	t_env			*sec;
	t_env			*temp;
	char			**command;
	int				*ids;
	int				i;
	int				id;
	int				size;
	int				temp_fd;
	t_frame			frame;
	int				fd[2];
}					t_info;

void				deletenode(t_env **env_list, char *key);
void				cd_oldpwd(t_env *env_list, t_env *pub_list);
void				cd_newpwd(t_env *env_list, t_env *pub_list);
void				ft_cd(char *path, t_env *env_list, t_env *pub_list);
void				signals_handler(int sig);
void				chck_echo(char *str, char flag, int fd, t_frame frame);
void				ft_wait_pid(t_info my_info);
void				check_path(t_data *data, t_comm *comm);
void				chck_before_herdoc_cmd(t_data *data, t_info my_info, int i);
int					open_input_fls(t_tkn_top redirection);
int					open_trunc_fls(t_tkn_top redirection);
void				run_herdoc(int *fd_heredoc, t_data *data, t_info my_info);
void				ft_loop(t_data *data, t_info my_info);
t_tkn				*tkn_initialize(int typ, char *val);
t_lxr				*lxr_initialize(char *ctt);
t_tkn				*tkn_nxt(t_lxr *lxr, t_env *env_list);

t_top_cmd			*ft_execution(char *ctt, t_env *env_list);
t_tkn				*ft_redirection(t_lxr *lxr, t_env *env_list);
t_tkn				*handle_her(t_lxr *lxr, t_env *env_list);

t_env				*ft_getenv(t_env *env_list, char *variable);
t_env				*get_env(char **i);
t_frame				open_fls(t_tkn_top redirection);

int					fill_temp_stdin(t_comm *comm);
void				exect(t_data *data, t_comm *comm, t_frame frame);
int					chck_built_in_cmd(t_data *data, t_comm *comm,
						t_frame frame);
char				*ft_join_echo(char **str, char flag);
void				chck_cmd_order(t_data *data, t_info *my_info);
void				all_free(t_top_cmd *top);
int					heredoc_return(int f_output, t_frame frame);
void				run_to_heredoc(t_comm **comm);
int					chck_built_in_cmd(t_data *data, t_comm *comm,
						t_frame frame);
char				*ft_join_echo(char **str, char flag);
void				close_pipe(int *fd);
void				check_in_files(int *stdin_temp, int *fd_in);
void				redirection_add(t_tkn_top *top, t_tkn *t);
void				ft_initialize(t_top_cmd *top);
void				node_add(t_top_cmd *top, t_comm *comm);
void				ft_move(t_lxr *lxr);
void				space_skip(t_lxr *lxr);
void				check_export_error(t_data *data, t_comm *comm);
void				check_cd_errors(t_data *data, t_comm *comm);
void				read_for_heredoc(t_comm *comm, int fd_in);
void				open_heredoc(t_comm **comm);
void				free_lst(t_env *env);
void				ft_error(char *i, char *l, int exit);
void				exec_cmd_before_herdoc(t_data *data);
void				check_cmd(t_comm *comm, t_data *data, t_frame frame);
void				exect(t_data *data, t_comm *comm, t_frame frame);
void				ft_execute(t_comm *comm, t_data *data, t_frame frame);
void				ft_pi_pe(t_data *data);
void				ft_env(t_data data, t_comm *comm, t_frame frame);
void				free_arry(char **a);
void				sort_env(t_env **env_list);
void				ft_un_set(t_env **env_list, char *del);
void				ft_setenv(t_env **env_list, char *key, char *val);
void				e_code(int i);
void				ft_redir_output_append(t_comm *comm, t_data *data);
void				ft_redir_output_trunc(t_comm *comm, t_data *data);
void				redir_input(t_comm *comm, t_data *data);
void				exec_last_node(t_data *data, t_info my_info);
void				exec_first_node(t_data *data, t_info my_info);
void				exec_other_node(t_data *data, t_info my_info);
void				exec_frst_cmd_before_herdoc(t_data *data, t_info my_info);
void				exec_last_command_before_heredoc(t_data *data,
						t_info my_info);
void				exec_other_cmd_before_herdoc(t_data *data, t_info my_info);
void				add_val_d(t_comm *comm, t_data *data, int j);
void				show_export_error(int *flag, int j, t_comm *comm);
void				ft_ex_it(char *var, char flag);
void				add_val(t_comm *comm, t_data *data, char **s, int i);
void				add_non_variable(t_comm *comm, t_data *data, char **s,
						int j);
void				add_un_val(t_comm *comm, t_data *data, char **s, int i);
void				exec_command(t_comm *comm, t_data *data, t_frame frame,
						char *p_comm);
void				init_fd(t_frame *frame);
void				display_ex_port(t_comm *comm, t_data data, t_frame frame);
void				cd_home(t_env *env_list, t_env *pub_list);
int					cmd_add(t_top_cmd *top, t_lxr *lxr, t_env *env_list);
int					get_word(char const *s, char c);
int					aft_dollar_check(t_lxr *lxr);
int					syntax_handle(char *val, t_tkn *t, t_top_cmd *top);
int					rederiction_handle(t_comm *red, t_tkn *tkn, t_top_cmd *top);
int					pipe_check(t_lxr *lxr, t_tkn *tkn, int l, t_top_cmd *top);
int					token_check(t_tkn *tkn, t_comm *red, int *i,
						t_top_cmd *top);
int					chck_built_in_cmd(t_data *data, t_comm *comm,
						t_frame frame);
int					ft_strcmp(char *str, char *p);
int					get_len(t_comm *comm);
int					get_exit_code(void);
int					is_variable(char *str);
int					chck_echo_flag(char *str);
int					chck_name(char *str);
int					ft_herdoc(t_data *data, t_comm *comm, t_frame frame);
int					cnt_cmd(t_comm *comm);
int					run_pwd(t_data data, t_comm *comm, t_frame frame);
char				*get_start(void);
char				*get_path(t_env *env_list, char *command);
char				*ft_join_echo(char **str, char flag);
char				*chck_spc(int i, char **str, char *res);
int					is_number(char *str);
int					node_load(t_comm *red, t_lxr *lxr, t_env *env_list,
						t_top_cmd *top);
char				*find_env(t_env *env_list, char *name);
char				*prime_str_collect(t_lxr *lxr, t_env *env_list, char cmd,
						int l);
char				*join_free(char *s, char *t);
char				*join_str(t_lxr *lxr, t_env *env_list, int l);
char				*aft_dollar(t_lxr *lxr, t_env *env_list);
char				*str_collect(t_lxr *lxr, t_env *env_list, char cmd, int l);
char				*get_data(t_lxr *lxr, t_env *env_list, int l);
char				*str_put(t_lxr *lxr, t_env *env_list, int l);
char				*unquoted_str(t_lxr *lxr, t_env *env_list, int l);
char				**ft_dup(char **av, char *val, int i);
int					run_echo(t_data data, t_comm *comm, t_frame frame);
int					add_variable(t_comm *comm, t_data *data, char **s, int j);
int					check_redirection(t_data *data, t_comm *comm);
int					herdoc_outside_pipe(t_data *data, t_comm *comm);
int					run_exit(t_data data, t_comm *comm);
int					run_cd(t_data data, t_comm *comm);
int					run_env(t_data data, t_comm *comm, t_frame frame);
int					run_unset(t_data *data, t_comm *comm);
void				ft_echo(t_comm *comm, char *str, char flag, t_frame frame);
int					run_ex_port(t_comm *comm, t_data *data, t_frame frame);
void				display_ex_port(t_comm *comm, t_data data, t_frame frame);
void				check_out_files(int *fd_out, int *f_output);
char				*get_var(t_lxr *lxr, t_env *env_list);
char				*utils_str(t_lxr *lxr);
#endif