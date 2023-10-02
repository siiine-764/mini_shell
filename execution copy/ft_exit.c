#include "../minishell_copy.h"

bool	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	run_exit(t_data data, t_comm *comm)
{
	if (!ft_strcmp(comm->flags[0], "exit"))
	{
		if (data.comm_num == 1)
		{
			ft_exit(comm->flags[1], '\0');
		}
		else
			ft_exit(comm->flags[1], 'p');
		return (true);
	}
	return (false);
}

void	check_export_error(t_data *data, t_comm *comm)
{
	int	i;

	(void)data;
	i = 0;
	while (comm->flags[++i])
		if (!is_properly_named(comm->flags[i]))
			set_exit_code(1);
}

void	check_cd_errors(t_data *data, t_comm *comm)
{
	if (comm->flags[1] == NULL
		|| ft_strcmp("~", comm->flags[1]) == 0)
		if (ft_getenv(data->env_list, "HOME") == NULL)
			set_exit_code(1);
}
