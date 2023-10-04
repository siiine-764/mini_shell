#include "../minishell_copy.h"

void	ft_exit(char flag, char *var)
{
	int	e;

	if (var == NULL)
	{
		set_exit_code(0);
		exit(0);
	}
	if (!is_number(var))
	{
		if (flag != 'e')
			ft_error(var, ": argument not found\n", 255);
	}
	else
	{
		e = ft_atoi(var);
		if (flag != '\0')
		{
			set_exit_code(e);
			return ;
		}
		printf("exit\n");
		g_global_vars.exit_code = e;
		set_exit_code(e);
		exit(e);
	}
}
