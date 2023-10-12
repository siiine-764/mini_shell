/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 03:02:20 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/12 03:02:20 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chck_built_in_cmd(t_data *data, t_comm *comm, t_frame frame)
{
	if (comm->flags[0] != NULL)
	{
		if (run_pwd(*data, comm, frame))
			return (true);
		else if (run_env(*data, comm, frame))
			return (true);
		else if (run_exit(*data, comm))
			return (true);
		else if (run_cd(*data, comm))
			return (true);
		else if (run_unset(data, comm))
			return (true);
		else if (run_ex_port(comm, data, frame))
			return (true);
		else if (run_echo(*data, comm, frame))
			return (true);
		return (false);
	}
	return (false);
}

void	ft_execute(t_comm *comm, t_data *data, t_frame frame)
{
	char	*p_comm;

	if (comm->flags[0] == NULL)
		return ;
	p_comm = get_path(data->env_list, comm->flags[0]);
	if (comm->flags[0][0] == '/' || comm->flags[0][0] == '.')
		check_cmd(comm, data, frame);
	else if (p_comm == NULL)
		ft_error(comm->flags[0], " :COMMAND NOT FOUND", COMMAND_NOT_FOUND);
	else
	{
		if (comm->flags[0][0])
			exec_command(comm, data, frame, p_comm);
		else
			ft_error(comm->flags[0], " :COMMAND NOT FOUND", COMMAND_NOT_FOUND);
	}
	free(p_comm);
	g_global_data.pid = -1;
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
