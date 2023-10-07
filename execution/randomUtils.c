#include "../minishell.h"

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

char	*get_promt(void)
{
	char	*command;

	command = readline("Minishell$> :");
	if (command && *command)
		add_history(command);
	return (command);
}

void	init_contex(t_frame *frame)
{
	frame->fd_in = STDIN_FILENO;
	frame->fd_out = STDOUT_FILENO;
}

void	walk_to_heredoc(t_comm **comm)
{
	while (*comm && (*comm)->heredoc->fst_tkn == NULL)
		*comm = (*comm)->nxt_comm;
}
