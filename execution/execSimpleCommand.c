#include "../minishell.h"

char	*get_path(t_env *env_list, char *c)
{
	t_p_data	data;

	data.path = ft_get_env_val(env_list, "PATH");
	if (data.path == NULL || c == NULL)
		return (NULL);
	data.i = -1;
	data.comm_path = ft_split(data.path, ':');
	free(data.path);
	while (data.comm_path[++data.i])
	{
		data.t = data.comm_path[data.i];
		data.comm_path[data.i] = ft_strjoin(data.comm_path[data.i], "/");
		free(data.t);
		data.t = data.comm_path[data.i];
		data.comm_path[data.i] = ft_strjoin(data.comm_path[data.i], c);
		free(data.t);
		if (access(data.comm_path[data.i], F_OK) == 0)
		{
			data.t = ft_strdup(data.comm_path[data.i]);
			free_2d_array(data.comm_path);
			return (data.t);
		}
	}
	free_2d_array(data.comm_path);
	return (NULL);
}

void	ft_error(char *i, char *l, int exit)
{
	ft_putstr_fd(i, STDERR_FILENO);
	ft_putendl_fd(l, STDERR_FILENO);
	set_exit_code(exit);
}

void	exec_command( t_data *data, t_comm *comm,
		t_frame frame, char *p_comm)
{
	int	s;

	g_global_vars.pid = fork();
	if (g_global_vars.pid == 0)
	{
		dup2(frame.fd_in, STDIN_FILENO);
		dup2(frame.fd_out, STDOUT_FILENO);
		execve(p_comm, comm->flags, data->env);
		perror(comm->flags[0]);
		exit(COMMAND_NOT_FOUND);
	}
	wait(&s);
	if (WIFEXITED(s))
		g_global_vars.pid = -1;
	set_exit_code(WEXITSTATUS(s));
}

void	run_excutable(t_comm *comm, t_data *data, t_frame frame)
{
	int	s;

	if (access(comm->flags[0], F_OK | X_OK) == 0)
	{
		if (fork() == 0)
		{
			if (access(comm->flags[0], F_OK | X_OK) == 0)
			{
				dup2(frame.fd_out, STDOUT_FILENO);
				dup2(frame.fd_in, STDIN_FILENO);
				execve(comm->flags[0], comm->flags, data->env);
			}
			exit(EXIT_SUCCESS);
		}
		wait(&s);
		if (WIFEXITED(s))
			set_exit_code(WEXITSTATUS(s));
	}
	else
	{
		set_exit_code(PERMISSION_DENIED);
		perror(comm->flags[0]);
	}
}

void	check_cmd(t_comm *comm, t_data *data, t_frame frame)
{
	int	s;
	int	fd[2];

	if (comm->flags[0][0] != '/')
		run_excutable(comm, data, frame);
	else if (access(comm->flags[0], F_OK) == 0)
	{
		pipe(fd);
		if (fork() == 0)
		{
			dup2(frame.fd_out, STDOUT_FILENO);
			dup2(frame.fd_in, STDIN_FILENO);
			execve(comm->flags[0], comm->flags, data->env);
			perror("execve");
			exit(PERMISSION_DENIED);
		}
		wait(&s);
		set_exit_code(WEXITSTATUS(s));
		return ;
	}
	else
	{
		set_exit_code(COMMAND_NOT_FOUND);
		perror(comm->flags[0]);
	}
}
