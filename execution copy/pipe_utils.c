
#include "../minishell_copy.h"
void	exec_first_node(t_data *data, t_info my_info)
{
	close(my_info.fd[0]);
	dup2(my_info.fd[1], STDOUT_FILENO);
	exec_node(data, data->comm, my_info.frame);
}

void	exec_last_node(t_data *data, t_info my_info)
{
	close(my_info.fd[0]);
	close(my_info.fd[1]);
	if (my_info.frame.heredoc_docs != 42)
	{
		close(my_info.frame.heredoc_docs);
		my_info.frame.heredoc_docs = open("/tmp/temp_output", O_RDONLY, 0644);
		if (my_info.frame.heredoc_docs == 0)
		{
			unlink("/tmp/trash");
			mt_info.frame.heredoc_docs = open("/tmp/trash", O_RDONLY | O_CREAT);
			dup2(my_info.frame.heredoc_docs, STDIN_FILENO);
		}
		else
		{
			dup2(my_info.frame.heredoc_docs, STDIN_FILENO);
		}
	}
	else
	{
		dup2(my_info.fd_temp, STDIN_FILENO);
	}
	exec_node(data, data->comm, my_info.frame);
}

void	exec_other_node(t_data *data, t_info my_info)
{
	close(my_info.fd[0]);
	if (my_info.frame.heredoc_docs != 42)
	{
		close(my_info.fd_temp);
		close(my_info.frame.heredoc_docs);
		my_info.frame.heredoc_docs = open("/tmp/temp_output", O_RDONLY);
		dup2(my_info.frame.heredoc_docs, STDIN_FILENO);
		dup2(my_info.fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(my_info.fd[1], STDOUT_FILENO);
		dup2(my_info.fd_temp, STDIN_FILENO);
	}
	exec_node(data, data->comm, my_info.frame);
}

void	wait_for_child(int *ids, int fd_temp, int i)
{
	int		sts;

	(void)fd_temp;
	while (--i >= 0)
		waitpid(ids[i], &sts, 0);
}

void	check_commands_order(t_data *data, t_info *my_info)
{
	pipe(my_info->fd);
	g_global_vars.pid = fork();
	if (g_global_vars.pid == 0)
	{
		if (my_info->i == 0)
			exec_first_node(data, *my_info);
		else if (my_info->i == my_info->size - 1)
			exec_last_node(data, *my_info);
		else
			exec_other_node(data, *my_info);
		exit(127);
	}
	my_info->fd_temp = dup(my_info->fd[0]);
}
