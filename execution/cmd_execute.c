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
	wait(NULL);
	if (WIFEXITED(s))
		g_global_data.pid = -1;
	e_code(WEXITSTATUS(s));
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
		wait(NULL);
		if (WIFEXITED(s))
			e_code(WEXITSTATUS(s));
	}
	else
	{
		e_code(PERMISSION_DENIED);
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
		wait(NULL);
		e_code(WEXITSTATUS(s));
		return ;
	}
	else
	{
		e_code(COMMAND_NOT_FOUND);
		perror(comm->flags[0]);
	}
}
