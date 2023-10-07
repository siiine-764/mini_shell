#include "../minishell.h"

void	ft_export(t_comm *comm, t_env *env, char *var)
{
	int	fd;

	fd = open_files(*comm->redirection).fd_out;
	if (fd == -1)
	{
		set_exit_code(1);
		return ;
	}
	if (var == NULL)
	{
		sort_list(&env);
		while (env)
		{
			ft_putstr_fd("DEC -x\t", fd);
			ft_putendl_fd(env->ctt, fd);
			env = env->nxt;
		}
	}
	else
	{
		ft_lstadd_front(&env, ft_lstnew(var));
		sort_list(&env);
	}
}

void	show_export_list(t_comm *comm, t_data data, t_frame frame)
{
	t_frame	fm;

	fm = open_files(*comm->redirection);
	if (fm.fd_in == -1 || fm.fd_out == -1)
	{
		set_exit_code(1);	
		return ;
	}
	while (data.pub_list && data.pub_list->ctt != NULL)
	{
		if (fm.fd_out == STDOUT_FILENO)
		{
			ft_putstr_fd("DEC -x  ", frame.fd_out);
			ft_putendl_fd(data.pub_list->ctt, frame.fd_out);
		}
		else
		{
			ft_putstr_fd("DEC -x  ", fm.fd_out);
			ft_putendl_fd(data.pub_list->ctt, fm.fd_out);
		}
		data.pub_list = data.pub_list->nxt;
	}
}

void	add_unexisted_variable(t_comm *comm, t_data *data,
		char **s, int j)
{
	ft_unset(&data->env_list, s[0]);
	ft_unset(&data->pub_list, s[0]);
	ft_lstadd_front(&(data)->env_list, ft_lstnew(ft_strdup(comm->flags[j])));
	ft_lstadd_front(&(data)->pub_list,
		ft_lstnew(ft_strdup(comm->flags[j])));
	sort_list(&data->pub_list);
}

void	add_existed_variable(t_comm *comm, t_data *data,
		char **s, int i)
{
	ft_unset(&data->env_list, s[0]);
	ft_unset(&data->pub_list, s[0]);
	ft_lstadd_front(&(data)->env_list, ft_lstnew(ft_strdup(comm->flags[i])));
	ft_lstadd_front(&(data)->pub_list, ft_lstnew(ft_strdup(comm->flags[i])));
		ft_lstnew(ft_strdup(comm->flags[i]));
	sort_list(&data->pub_list);
}

bool	run_export(t_comm *comm, t_data *data, t_frame frame)
{
	int			flag;
	int			j;

	flag = 0;
	j = 0;
	if (ft_strcmp(comm->flags[0], "export")
		&& ft_strcmp(comm->flags[0], "EXPORT"))
		return (false);
	if (comm->flags[1] == NULL)
		show_export_list(comm, *data, frame);
	else
	{
		while (comm->flags[++j])
		{
			if (is_properly_named(comm->flags[j]))
				add_properly_named_word(comm, data, j);
			else
				show_export_error(&flag, j, comm);
		}
	}
	return (true);
}
