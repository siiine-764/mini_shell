#include "../minishell.h"

void	ft_pwd(t_data data, t_comm *comm, t_frame frame)
{
	t_frame		fm;
	char		dir[PATH_MAX];

	fm = open_files(*comm->redirection);
	if (fm.fd_out == -1 || fm.fd_in == -1)
	{
		set_exit_code(1);
		return ;
	}
	getcwd(dir, sizeof(dir));
	ft_setenv(&data.env_list, "PWD", dir);
	ft_setenv(&data.pub_list, "PWD", dir);
	if (fm.fd_out == STDOUT_FILENO)
		ft_putendl_fd(dir, frame.fd_out);
	else
		ft_putendl_fd(dir, fm.fd_out);
	set_exit_code(EXIT_SUCCESS);
}

bool	run_pwd(t_data data, t_comm *comm, t_frame frame)
{
	if (!ft_strcmp(comm->flags[0], "pwd"))
	{
		ft_pwd(data, comm, frame);
		return (true);
	}
	return (false);
}
=======

#include "../minishell_copy.h"

void	ft_pwd(t_data data, t_comm *comm, t_frame frame)
{
	t_frame		fm;
	char		dir[PATH_MAX];

	fm = open_files(*comm->redirection);
	if (fm.fd_out == -1 || fm.fd_in == -1)
	{
		set_exit_code(1);
		return ;
	}
	getcwd(dir, sizeof(dir));
	ft_setenv(&data.env_list, "PWD", dir);
	ft_setenv(&data.pub_list, "PWD", dir);
	if (fm.fd_out == STDOUT_FILENO)
		ft_putendl_fd(dir, frame.fd_out);
	else
		ft_putendl_fd(dir, fm.fd_out);
	set_exit_code(EXIT_SUCCESS);
}

bool	run_pwd(t_data data, t_comm *comm, t_frame frame)
{
	if (!ft_strcmp(comm->flags[0], "pwd"))
	{
		ft_pwd(data, comm, frame);
		return (true);
	}
	return (false);
}
>>>>>>> 50906c57125dc70873f888bbbe30f3382ad8de2f
