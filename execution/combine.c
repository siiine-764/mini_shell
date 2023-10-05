#include "../minishell.h"

void	set_exit_code(int i)
{
	if (i == SYNTAX_ERROR_EXIT)
		g_global_data.exit_code = i;
	else
	{
		while (i > 255)
			i -= 256;
		g_global_data.exit_code = i;
	}
}

int	get_exit_code(void)
{
	return (g_global_data.exit_code);
}

bool	check_redirection(t_data *data, t_comm *comm)
{
	if (comm->redirection->fst_tkn != NULL)
	{
		if (comm->redirection->fst_tkn->tkn == T_OUT)
			ft_redirect_output_trunc_mode(data, comm);
		else if (comm->redirection->fst_tkn->tkn == T_APPEND)
			ft_redirect_output_append_mode(comm, data);
		else if (comm->redirection->fst_tkn->tkn == T_IN)
			redirect_input(data, comm);
		return (true);
	}
	else
		return (false);
}
