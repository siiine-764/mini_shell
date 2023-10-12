/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomUtils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:33:51 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/10 18:33:51 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp(char *str, char *p)
{
	int	i;

	i = 0;
	while (str[i] || p[i])
	{
		if (str[i] != p[i])
			return (str[i] - p[i]);
		i++;
	}
	return (0);
}

void	signals_handler(int sig)
{
	(void)sig;
	printf("\n");
    rl_on_new_line();
    //rl_replace_line("", 0);
    rl_redisplay();
}

char	*get_start(void)
{
	char	*command;

	signal(SIGINT, signals_handler);
	signal(SIGQUIT, SIG_IGN);
	command = readline("Minishell$> ");
	if (command && *command)
		add_history(command);
	return (command);
}

void	init_fd(t_frame *frame)
{
	frame->fd_in = STDIN_FILENO;
	frame->fd_out = STDOUT_FILENO;
}

void	run_to_heredoc(t_comm **comm)
{
	while (*comm && (*comm)->heredoc->fst_tkn == NULL)
		*comm = (*comm)->nxt_comm;
}
