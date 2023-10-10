/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execSimpleCommand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:34:38 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/10 18:34:38 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(t_env *env_list, char *command)
{
	t_p_data	data;

	data.path = find_env(env_list, "PATH");
	if (data.path == NULL || command == NULL)
		return (NULL);
	data.i = -1;
	data.p_comm = ft_split(data.path, ':');
	free(data.path);
	while (data.p_comm[++data.i])
	{
		data.temp = data.p_comm[data.i];
		data.p_comm[data.i] = ft_strjoin(data.p_comm[data.i], "/");
		free(data.temp);
		data.temp = data.p_comm[data.i];
		data.p_comm[data.i] = ft_strjoin(data.p_comm[data.i], command);
		free(data.temp);
		if (access(data.p_comm[data.i], F_OK) == 0)
		{
			data.temp = ft_strdup(data.p_comm[data.i]);
			free_2d(data.p_comm);
			return (data.temp);
		}
	}
	free_2d(data.p_comm);
	return (NULL);
}

void	ft_error(char *i, char *l, int exit)
{
	ft_putstr_fd(i, STDERR_FILENO);
	ft_putendl_fd(l, STDERR_FILENO);
	set_exit_code(exit);
}

void	exec_command(t_comm *comm, t_data *data,
		t_frame frame, char *p_comm)
{
	int	s;

	g_global_data.pid = fork();
	if (g_global_data.pid == 0)
	{
		dup2(frame.fd_in, STDIN_FILENO);
		dup2(frame.fd_out, STDOUT_FILENO);
		execve(p_comm, comm->flags, data->env);
		perror(comm->flags[0]);
		exit(COMMAND_NOT_FOUND);
	}
	wait(&s);
	if (WIFEXITED(s))
		g_global_data.pid = -1;
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
