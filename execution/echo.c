#include "../minishell.h"

void	check_echo(char *str, char flag, int fd, t_frame frame)
{
	if (flag == 'n')
	{
		if (fd != STDOUT_FILENO)
			ft_putstr_fd(str, fd);
		else
			ft_putstr_fd(sre, frame.fd_out);
	}
	else
	{
		if (fd != STDOUT_FILENO)
			ft_putendl_fd(str, fd);
		else
			ft_putendl_fd(str, frame.fd_out);
	}
}

void	ft_echo(t_comm *comm, char *str, char flag, t_frame frame)
{
	int		fd;

	fd = open_files(*comm->redirection).fd_out;
	if (fd == -1)
	{
		set_exit_code(1);
		return ;
	}
	if (str == NULL)
	{
		write(fd, "\n", 2);
		return ;
	}
	check_echo(str, flag, fd, frame);
	free(str);
	set_exit_code(EXIT_SUCCESS);
}

int	check_echo_flag(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (ft_strcmp(str, "-") == 0)
		return (false);
	if (str[i++] != '-')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i += 1;
	}
	return (true);
}

char	*check_for_space( int i, char **str, char *res)
{
	char	*val;

	if (str[i + 1] && str[i][0] != '\0')
	{
		val = res;
		res = ft_strjoin(res, " ");
		free(val);
	}
	return (res);
}

bool	exec_echo(t_data data, t_comm *comm, t_frame frame)
{
	(void)data;
	if (ft_strcmp(comm->flags[0], "echo") == 0)
	{
		if (comm->flags[1] == NULL)
			ft_echo(comm, NULL, '0', frame);
		else if ((check_echo_flag(comm->flags[1])))
			ft_echo(comm, join_for_echo(comm->flags, 'n'), 'n', frame);
		else
			ft_echo(comm, join_for_echo(comm->flags, '\0'), '\0', frame);
		return (true);
	}
	return (false);
}
