#include "../minishell.h"

int	open_input_fls(t_tkn_top redirection)
{
	int	fd_in;

	if (redirection.fst_tkn->tkn == T_IN)
	{
		fd_in = open(redirection.fst_tkn->val, O_RDONLY);
		if (fd_in == -1)
			perror(redirection.fst_tkn->val);
		return (fd_in);
	}
	return (INT_MIN);
}

int	open_trunc_fls(t_tkn_top redirection)
{
	int	fd_out;

	if (redirection.fst_tkn->tkn == T_OUT)
	{
		fd_out = open(redirection.fst_tkn->val, \
			O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd_out == -1)
			perror(redirection.fst_tkn->val);
		return (fd_out);
	}
	return (INT_MIN);
}