#include "../minishell_copy.h"

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
