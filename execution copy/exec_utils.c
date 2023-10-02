#include "../minishell_copy.h"

int	get_len(t_comm *comm)
{
	int	i;

	i = 0;
	while (comm)
	{
		i += 1;
		comm = comm->nxt_comm;
	}
	return (i);
}

void	exec_node(t_data *data, t_comm *comm, t_frame frame)
{
	int		j;

	j= 0;
	if (check_built_in_commands(data, comm, frame) == false)
	{
		if (!check_redirection(data, comm))
		{
			if (comm->heredoc->fst_tkn == NULL)
			{
				ft_execute(comm, data, frame);
				wait(NULL);
			}
		}
	}
}

int	check_built_in_commands(t_data *data, t_comm *comm, t_frame frame)
{
	if (comm->flags[0] != NULL)
	{
		if (run_pwd(*data, comm, frame))
			return (true);
		else if (run_env(*data, comm, frame))
			return (true);
		else if (run_exit(*data, comm))
			return (true);
		else if (run_cd(*data, comm))
			return (true);
		else if (run_unset(data, comm))
			return (true);
		else if (run_export(comm, data, frame))
			return (true);
		else if (exec_echo(*data, comm, frame))
			return (true);
		return (false);
	}
	return (false);
}

void	ft_execute(t_comm *comm, t_data *data, t_frame frame)
{
	char	*p_comm;

	if (comm->flags[0] == NULL)
		return ;
	p_comm = get_path(data->env_list, comm->flags[0]);
	if (comm->flags[0][0] == '/' || comm->flags[0][0] == '.')
		check_cmd(comm, data, frame);
	else if (p_comm == NULL)
		ft_error(comm->flags[0], " :command not found", COMMAND_NOT_FOUND);
	else
	{
		if (comm->flags[0][0])
			exec_command(comm, data, frame, p_comm);
		else
			ft_error(comm->flags[0], " :command not found",
				COMMAND_NOT_FOUND);
	}
	free(p_comm);
	g_global_vars.pid = -1;
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
