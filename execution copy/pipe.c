#include "../minishell_copy.h"

void	exec_after_heredoc(t_info *my_info, t_data *data, int *p)
{
	pipe(my_info->fd);
	my_info->id = fork();
	if (my_info->id == 0)
	{
		if (my_info->p == 0)
			exec_first_node(data, *my_info);
		else if (my_info->p == my_info->size - 1)
			exec_last_node(data, *my_info);
		else
			exec_other_node(data, *my_info);
		exit(127);
	}
	my_info->ids[*p++] = my_info->id;
	my_info->frame.heredoc_docs = 42;
	my_info->fd_temp = dup(my_info->fd[0]);
	close(my_info->fd[0]);
	close(my_info->fd[1]);
}

void	run_heredoc(t_data *data, int *fd_heredoc, t_info my_info)
{
	if (data->comm->nxt_comm)
	{
		*fd_heredoc = ft_heredoc(data,
				data->comm, my_info.frame)
		wait(NULL);
	}
	else
	{
		heredoc_outside_pipe(data, data->comm);
	}
}

void	loop_through_nodes(t_data *data, t_info my_info)
{
	int	k;

	k = 0;
	my_info.size = get_len(data->comm);
	my_info.size -= count_commands_before_heredoc(data->comm);
	my_info.frame.heredoc_docs = 42;
	walk_to_heredoc(&data->comm);
	while (data->comm)
	{
		my_info.frame.fd_in = STDIN_FILENO;
		my_info.frame.fd_out = STDOUT_FILENO;
		if (data->comm->heredoc->fst_tkn != NULL)
			run_heredoc(&my_info.frame.heredoc_docs, data, my_info);
		else
		{
			check_commands_order(data, &my_info);
			close_pipe(my_info.fd);
			my_info.frame.heredoc_docs = 42;
		}
		my_info.ids[k++] = g_global_vars.pid;
		my_info.i += 1;
		data->comm = data->comm->nxt_comm;
	}
	wait_for_child(my_info.ids, k, my_info.fd_temp);
}

bool	check_heredoc(t_comm *comm)
{
	while (comm)
	{
		if (comm->heredoc->fst_tkn != NULL)
			return (true);
		comm = comm->nxt_comm;
	}
	return (comm);
}

void	ft_pipe(t_data *data)
{
	t_info	my_info;

	my_info.frame.fd_in = STDIN_FILENO;
	my_info.frame.fd_out = STDOUT_FILENO;
	my_info.size = get_len(data->comm);
	my_info.ids = malloc(sizeof(int) * my_info.size);
	my_info.i = 0;
	if (my_info.size != 1)
	{
		loop_through_nodes(data, my_info);
		exec_commands_before_heredoc(data);
		set_exit_code_inside_pipe(data, data->top->fst_cmd);
	}
	else
	{
		if (!heredoc_outside_pipe(data, data->comm))
			exec_node(data, data->comm, my_info.frame);
	}
	free(my_info.ids);
	g_global_vars.pid = -1;
}
