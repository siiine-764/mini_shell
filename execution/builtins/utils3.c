#include "../../minishell.h"

void	add_un_val(t_comm *comm, t_data *data,
		char **s, int j)
{
	ft_un_set(&data->env_list, s[0]);
	ft_un_set(&data->pub_list, s[0]);
	ft_lstadd_back(&(data)->env_list, ft_lstnew(ft_strdup(comm->flags[j])));
	ft_lstadd_back(&(data)->pub_list,
		ft_lstnew(ft_strdup(comm->flags[j])));
}

void	add_val(t_comm *comm, t_data *data,
		char **s, int i)
{
	ft_un_set(&data->env_list, s[0]);
	ft_un_set(&data->pub_list, s[0]);
	ft_lstadd_back(&(data)->env_list, ft_lstnew(ft_strdup(comm->flags[i])));
	ft_lstadd_back(&(data)->pub_list, ft_lstnew(ft_strdup(comm->flags[i])));
		ft_lstnew(ft_strdup(comm->flags[i]));
	sort_env(&data->pub_list);
}
