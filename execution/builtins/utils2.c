#include "../../minishell.h"

void	chck_echo(char *str, char flag, int fd, t_frame frame)
{
	if (flag == 'n')
	{
		if (fd != STDOUT_FILENO)
			ft_putstr_fd(str, fd);
		else
			ft_putstr_fd(str, frame.fd_out);
	}
	else
	{
		if (fd != STDOUT_FILENO)
			ft_putendl_fd(str, fd);
		else
			ft_putendl_fd(str, frame.fd_out);
	}
}

int	chck_name(char *str)
{
	return (ft_isalpha(str[0]) || str[0] == '_');
}

int	is_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && i - 1 >= 0 && str[i - 1] != '=')
			return (true);
		i++;
	}
	return (false);
}

int	is_number(char *str)
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
