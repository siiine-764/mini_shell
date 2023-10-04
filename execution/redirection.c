#include "../minishell.h"

void	ft_redirect_output_append_mode(t_comm *comm, t_data *data)
{
	t_frame	frame;

	frame.heredoc_docs = -1;
	frame = open_files(*comm->redirection);
	if (frame.fd_in == -1 || frame.fd_out == -1)
	{
		set_exit_code(1);
		return ;
	}
	if (comm->flags[0] != NULL)
		if (!check_built_in_commands(data, comm, frame))
			ft_execute(comm, data, frame);
	set_exit_code(EXIT_SUCCESS);
}

void	ft_redirect_output_trunc_mode(t_comm *comm, t_data *data)
{
	t_frame	frame;

	frame.heredoc_docs = -1;
	frame = open_files(*comm->redirection);
	if (frame.fd_in == -1 || frame.fd_out == -1)
	{
		set_exit_code(1);
		return ;
	}
	if (comm->flags[0] != NULL)
	{
		if (!check_built_in_commands(data, comm, frame))
			ft_execute(comm, data, frame);
	}
	set_exit_code(EXIT_SUCCESS);
}

void	redirect_input(t_comm *comm, t_data *data)
{
	t_frame	frame;

	frame.heredoc_docs = -1;
	frame = open_files(*comm->redirection);
	if (frame.fd_out == -1 || frame.fd_in == -1)
	{
		set_exit_code(1);
		return ;
	}
	else if (comm->flags[0] != NULL)
		if (!check_built_in_commands(data, comm, frame))
			ft_execute(comm, data, frame);
	set_exit_code(EXIT_SUCCESS);
}

void	exec_herdoc_command(t_comm *comm, t_data *data, t_frame frame)
{
	char	*path;

	if (comm->flags[0] != NULL)
	{
		path = get_path(data->env_list, comm->flags[0]);
		if (path)
		{
			if (fork() == 0)
			{
				dup2(frame.heredoc_docs, STDIN_FILENO);
				dup2(frame.fd_out, STDOUT_FILENO);
				execve(path, comm->flags, data->env);
				perror("exe");
				exit(COMMAND_NOT_FOUND);
			}
		}
		else
			ft_error(comm->flags[0],
				": COMMAND NOT FOUND\n", COMMAND_NOT_FOUND);
	}
	set_exit_code(EXIT_SUCCESS);
}

int	ft_heredoc(t_data *data, t_comm *comm, t_frame frame)
{
	int		output;
	int		stdin_temp;

	output = 42;
	stdin_temp = fill_temp_stdin(comm);
	frame = open_files(*comm->redirection);
	if (frame.fd_in == -1 || frame.fd_out == -1)
	{
		set_exit_code(1);
		return (0);
	}
	check_out_files(&output, &frame.fd_out);
	check_in_files(&frame.fd_in, &stdin_temp);
	frame.fd_out = dup(frame.fd_out);
	if (!check_built_in_commands(data, comm, frame))
	{
		ft_execute(comm, data, frame);
		wait(NULL);
		close(frame.fd_out);
	}
	unlink("tmp/temp");
	return (heredoc_return(output, frame));
}
