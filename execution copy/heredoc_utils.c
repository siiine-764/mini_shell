#include "../minishell_copy.h"

void	exec_first_command_before_heredoc(t_data *data, t_info my_info)
{
	close(my_info.fd[0]);
	dup2(my_info.fd[1], STDOUT_FILENO);
	exec_node(data, data->comm, my_info.frame);
}

void	exec_last_command_before_heredoc(t_data *data, t_info my_info)
{
	if (data->comm->redirection->fst_tkn == NULL && data->comm->nxt_comm)
		dup2(my_info.fd[1], STDOUT_FILENO);
	else
		close(my_info.fd[1]);
	close(my_info.fd[0]);
	dup2(my_info.temp_fd, STDIN_FILENO);
	exec_node(data, data->comm, my_info.frame);
}

void	exec_other_command_before_heredoc(t_data *data, t_info my_info)
{
	close(my_info.fd[0]);
	dup2(my_info.fd[1], STDOUT_FILENO);
	dup2(my_info.temp_fd, STDIN_FILENO);
	exec_node(data, data->comm, my_info.frame);
}

void	open_heredoc(t_comm **comm)
{
	char	*l;

	if ((*comm)->heredoc->fst_tkn == NULL
		|| (*comm)->heredoc->fst_tkn->nxt == NULL)
		return ;
	while (*comm)
	{
		if ((*comm)->heredoc->fst_tkn->nxt == NULL)
			return ;
		while (true)
		{
			l = readline(">");
			if (l == NULL
				|| ft_strcmp(l, (*comm)->heredoc->fst_tkn->val) == 0)
				break ;
			free(l);
		}
		(*comm)->heredoc->fst_tkn = (*comm)->heredoc->fst_tkn->nxt;
	}
}

bool	heredoc_outside_pipe(t_data *data, t_comm *comm)
{
	t_frame	frame_temp;
	t_frame	frame;

	open_heredoc(&comm);
	unlink("/tmp/temp");
	frame.fd_in = open("/tmp/temp", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (comm->heredoc->fst_tkn == NULL)
		return (false);
	read_for_heredoc(comm, frame.fd_in);
	frame_temp = open_files(*data->comm->redirection);
	if (frame_temp.fd_in == -1 || frame_temp.fd_out == -1)
	{
		set_exit_code(1);
		return (true);
	}
	frame.fd_out = dup(frame_temp.fd_out);
	if (frame_temp.fd_in != STDIN_FILENO)
		frame.fd_in = dup(frame_temp.fd_in);
	else
		frame.fd_in = dup(frame.fd_in);
	if (!check_built_in_commands(data, comm, frame))
		ft_execute(comm, data, frame);
	wait(NULL);
	unlink("/tmp/temp");
	return (true);
}
