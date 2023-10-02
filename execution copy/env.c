#include "../minishell_copy.h"

void	ft_env(t_data data, t_comm *comm, t_frame frame)
{
	t_frame	fd;

	fd = open_files(*comm->redirection);
	if (fd.fd_in == -1 || fd.fd_in == -1)
	{
		set_exit_code(1);
		return ;
	}
	while (data.env_list)
	{
		if (data.env_list->ctt)
		{
			if (fd.fd_out == STDOUT_FILENO)
				ft_putendl_fd(data.env_list->ctt, frame.fd_out);
			else
				ft_putendl_fd(data.env_list->ctt, fd.fd_out);
		}
		data.env_list = data.env_list->nxt;
	}
}

bool	run_env(t_data data, t_comm *comm, t_frame frame)
{
	if (!ft_strcmp(comm->flags[0], "env"))
	{
		ft_env(data, comm, frame);
		return (true);
	}
	return (false);
}

int	is_properly_named(char *str)
{
	return (ft_isalpha(str[0]) || str[0] == '_');
}

t_env	*ft_getenv(t_env *env_list, char *variable)
{
	char	*val;
	char	**j;
	int		c;

	while (env_list)
	{
		j = ft_split(env_list->ctt, '=');
		val = ft_strdup(j[0]);
		c = 0;
		free_2d_array(j);
		if (!val || !*val)
			return (NULL);
		if (ft_strcmp(val, variable) == 0)
		{
			free(val);
			return (env_list);
		}
		env_list = env_list ->nxt;
		free(val);
	}
	return (NULL);
}

void	ft_setenv(t_env **env_list, char *variable, char *value)
{
	t_env	*str;
	char	*res;
	char	*j;

	str = ft_getenv(*env_list, variable);
	if (str == NULL)
	{
		res = ft_strjoin(variable, "=");
		j = res;
		var = ft_strjoin(res, value);
		free(j);
		ft_lstadd_back(env_list, ft_lstnew(res));
	}
	else
	{
		ft_unset(env_list, variable);
		ft_setenv(env_list, variable, value);
	}
}
