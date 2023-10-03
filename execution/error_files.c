#include "../minishell.h"

void	check_command_error(t_data *data, t_comm *comm)
{
	(void)data;
	if (access(comm->flags[0], F_OK | X_OK) != 0)
		set_exit_code(PERMISSION_DENIED);
	else
		set_exit_code(0);
}

void	check_command_error_2(t_data *data, t_comm *comm)
{
	(void)data;
	if (access(comm->flags[0], F_OK | X_OK) != 0)
		set_exit_code(PERMISSION_DENIED);
	else
		set_exit_code(0);
}

void	check_path(t_data *data, t_comm *comm)
{
	char	*p;

	p = get_path(data->env_list, comm->flags[0]);
	if (p == NULL)
		set_exit_code(COMMAND_NOT_FOUND);
	else
		set_exit_code(0);
	free(p);
}

void	check_files(t_tkn_top redirection)
{
	int	output;

	while (redirection.fst_tkn != NULL)
	{
		if (redirection.fst_tkn->tkn == T_IN)
		{
			output = open(redirection.fst_tkn->val, O_RDONLY);
			if (output == -1)
				set_exit_code(1);
		}
		redirection.fst_tkn = redirection.fst_tkn->nxt;
	}
}

void	set_exit_code_inside_pipe(t_data *data, t_comm *comm)
{
	int		i;

	i = 0;
	while (comm)
	{
		if (comm->flags[0])
		{
			if (ft_strcmp(comm->flags[0], "exit") == 0)
				ft_exit(comm->flags[1], 'e');
			else if (ft_strcmp(comm->flags[0], "export") == 0)
				check_export_error(data, comm);
			else if (ft_strcmp(comm->flags[0], "cd") == 0)
				check_cd_errors(data, comm);
			else if (comm->flags[0][0] == '/')
				check_command_error(data, comm);
			else if (comm->flags[0][0] == '.')
				check_command_error_2(data, comm);
			else
				check_path(data, comm);
		}
		check_files(*comm->redirection);
		comm = comm->nxt_comm;
	}
}
