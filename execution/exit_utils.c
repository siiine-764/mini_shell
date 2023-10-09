#include "../minishell.h"

void	check_export_error(t_data *data, t_comm *comm)
{
	int	i;

	(void)data;
	i = 0;
	while (comm->flags[++i])
		if (!is_properly_named(comm->flags[i]))
			exit(1);
}

void	check_cd_errors(t_data *data, t_comm *comm)
{
	if (comm->flags[1] == NULL 
		|| ft_strcmp("~", comm->flags[1]) == 0)
		if (ft_getenv(data->env_list, "HOME") == NULL)
			exit(1);
}
