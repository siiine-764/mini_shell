/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:54:35 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/09 18:54:35 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	display_ex_port(t_comm *comm, t_data data, t_frame frame)
{
	frame = open_fls(*comm->redirection);
	if (frame.fd_in == -1 || frame.fd_out == -1)
	{
		e_code(1);	
		return ;
	}
	while (data.pub_list && data.pub_list->ctt != NULL)
	{
		if (frame.fd_out == STDOUT_FILENO)
		{
			ft_putstr_fd("declare -x  ", frame.fd_out);
			ft_putendl_fd(data.pub_list->ctt, frame.fd_out);
		}
		else
		{
			ft_putstr_fd("declare -x  ", frame.fd_out);
			ft_putendl_fd(data.pub_list->ctt, frame.fd_out);
		}
		data.pub_list = data.pub_list->nxt;
	}
}

void	add_un_val(t_comm *comm, t_data *data,
		char **s, int j)
{
	ft_un_set(&data->env_list, s[0]);
	ft_un_set(&data->pub_list, s[0]);
	ft_lstadd_back(&(data)->env_list, ft_lstnew(ft_strdup(comm->flags[j])));
	ft_lstadd_back(&(data)->pub_list,
		ft_lstnew(ft_strdup(comm->flags[j])));
	// sort_env(&data->pub_list);
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

int	run_ex_port(t_comm *comm, t_data *data, t_frame frame)
{
	int			flag;
	int			j;

	flag = 0;
	j = 0;
	if (ft_strcmp(comm->flags[0], "export"))
		return (false);
	if (comm->flags[1] == NULL)
		display_ex_port(comm, *data, frame);
	else
	{
		while (comm->flags[++j])
		{
			if (chck_name(comm->flags[j]))
				add_val_d(comm, data, j);
			else
				show_export_error(&flag, j, comm);
		}
	}
	return (true);
}
