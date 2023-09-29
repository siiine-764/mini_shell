#include "../minishell_copy.h"

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
	int	out_file;

	while (redirection.fst_tkn != NULL)
	{
		if (redirection.fst_tkn->tkn == T_IN)
		{
			out_file = open(redirection.fst_tkn->val, O_RDONLY);
			if (out_file == -1)
				set_exit_code(1);
		}
		redirection.fst_tkn = redirection.fst_tkn->nxt;
	}
}

void	set_exit_code_inside_pipe(t_vars *vars, t_command *command)
{
	int		i;

	i = 0;
	while (command)
	{
		if (command->flags[0])
		{
			if (ft_strcmp(command->flags[0], "exit") == 0)
				ft_exit(command->flags[1], 'e');
			else if (ft_strcmp(command->flags[0], "export") == 0)
				check_export_error(vars, command);
			else if (ft_strcmp(command->flags[0], "cd") == 0)
				check_cd_errors(vars, command);
			else if (command->flags[0][0] == '/')
				check_command_error(vars, command);
			else if (command->flags[0][0] == '.')
				check_command_error_2(vars, command);
			else
				check_path(vars, command);
		}
		check_files(*command->redi);
		command = command->next_command;
	}
}
