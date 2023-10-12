/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 04:35:01 by hben-mes          #+#    #+#             */
/*   Updated: 2023/10/12 04:35:40 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_routine(t_data *data)
{
	char	*command;

	command = get_start();
	if (command == NULL)
	{
		free(command);
		exit(EXIT_SUCCESS);
	}
	else if (*command)
	{
		data->top = ft_execution(command, data->env_list);
		if (data->top != NULL)
		{
			data->comm = data->top->fst_cmd;
			data->comm_num = get_len(data->comm);
			if (data->comm != NULL)
				ft_pi_pe(data);
			all_free(data->top);
		}
	}
	free(command);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	data->env = env;
	data->env_list = get_env(data->env);
	data->pub_list = get_env(data->env);
	g_global_data.pid = -1;
	g_global_data.signal_flag = 0;
	g_global_data.e = 0;
	while (true)
	{
		minishell_routine(data);
	}
}
