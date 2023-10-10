#include "minishell.h"

void	sig_handler(int sig)
{
	g_global_data.sig_typ = sig;
	if ((sig == SIGINT || sig == SIGQUIT) && g_global_data.pid != -1)
	{
		if (!kill(g_global_data.pid, sig))
			g_global_data.signal_flag = 1;
	}
	else
	{
		g_global_data.signal_flag = 0;
		if (sig == SIGINT)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			set_exit_code(1);
			rl_on_new_line();
			// rl_replace_line("", 0);
			rl_redisplay();
		}
		else 
		if (sig == SIGQUIT)
		{
			ft_putchar_fd('\r', STDOUT_FILENO);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	minishell_routine(t_data *data)
{
	char	*command;

//SIGINT is a signal generated when a user presses Control-C

	// signal(SIGINT, sig_handler);
	command = get_promt();
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
				ft_pipe(data);
			all_free(data->top);
		}
	}
	// signal(SIGQUIT, sig_handler);
	free(command);
}

void	set_signals_exit_code(void)
{
	if (g_global_data.signal_flag == 1)
	{
		if (g_global_data.sig_typ == SIGQUIT)
		{
			ft_putstr_fd("QUIT: 3\n", STDOUT_FILENO);
			g_global_data.e = CNTRL_BACKSLASH;
		}
		else
		{
			ft_putchar_fd('\n', 1);
			g_global_data.e = CNTRL_C;
		}
		g_global_data.signal_flag = 0;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	data->env = env;
	data->env_list = get_env_list(data->env);
	data->pub_list = get_env_list(data->env);
	g_global_data.pid = -1;
	g_global_data.signal_flag = 0;
	g_global_data.e = 0;
	while (true)
	{
		set_signals_exit_code();
		minishell_routine(data);
	}
}