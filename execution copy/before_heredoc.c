#include "../minishell_copy.h"

bool	heredoc_exist(t_data *data)
{
	while (data->comm)
	{
		if (data->comm->heredoc->fst_tkn != NULL)
			return (true);
		data->comm = data->comm->nxt_comm;
	}
	return (false);
}

int	count_commands_before_heredoc(t_comm *comm)
{
	int	i;

	i = 0;
	while (comm && comm->heredoc->fst_tkn == NULL )
	{
		comm = comm->nxt_comm;
		i += 1;
	}
	return (i);
}

void	check_before_heredoc_commands(t_data *data, t_elem elems, int i)
{
	if (i == 0)
		exec_first_command_before_heredoc(data, elems);
	else if (i == data.size - 1)
		exec_last_command_before_heredoc(data, elems);
	else
		exec_other_command_before_heredoc(data, elems);
}

void	run_commands_before_heredoc(t_data *data, t_elem elems, int i)
{
	g_global_vars.pid = fork();
	if (g_global_vars.pid == 0)
	{
		check_before_heredoc_commands(data, elems, i);
		exit(0);
	}
}

void	exec_commands_before_heredoc(t_data *data)
{
	int		j;
	t_elem	elems;

	j = 0;
	elems.size = count_commands_before_heredoc(data->top->fst_cmd);
	elems.ids = malloc(sizeof(int) * elems.size);
	data->comm = data->top->fst_cmd;
	while (i < elems.size && data->comm)
	{
		elems.contex.fd_in = STDIN_FILENO;
		elems.contex.fd_out = STDOUT_FILENO;
		pipe(elems.fd);
		run_commands_before_heredoc(data, elems, i);
		elems.ids[i++] = g_global_vars.pid;
		data->comm = data->comm->nxt_comm;
		elems.temp_fd = dup(elems.fd[0]);
		close_pipe(elems.fd);
	}
	wait_for_child(elems.ids, i, elems.temp_fd);
	free(elems.ids);
}
