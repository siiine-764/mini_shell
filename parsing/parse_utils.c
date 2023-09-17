
#include "../MiniShell.h"

void	redirection_add(t_tkn_top *top, t_tkn *t)
{
	t_tkn	*temp;

	temp = top->fst_tkn;
	if (temp == NULL)
	{
		top->fst_tkn = t;
		return ;
	}
	while (temp->nxt)
		temp = temp->nxt;
	temp->nxt = t;
}

void	node_add(t_top_cmd *top, t_comm *comm)
{
	t_comm	*temp;

	temp = top->fst_cmd;
	if (temp == NULL)
	{
		top->fst_cmd = comm;
		top->size += 1;
		comm->nxt_comm = NULL;
		return ;
	}
	while (temp->nxt_comm)
		temp = temp->nxt_comm;
	temp->nxt_comm = comm;
	top->size += 1;
	comm->nxt_comm = NULL;
}

char	**ft_dup(char **av, char *data, int i)
{
	int		j;
	char	**t;

	t = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j < i - 1)
	{
		t[j] = av[j];
		j++;
	}	
	t[j] = ft_strdup(data);
	t[j + 1] = NULL;
	free(av);
	return (t);
}

void	put_exit(int i)
{
	if (i == SYNTAX_ERROR_EXIT)
		g_global_vars.exit_code = i;
	else
	{
		while (i > 255)
			i -= 256;
		g_global_vars.exit_code = i;
	}
}

int	syntax_handle(char *data, t_tkn *tk, t_top_cmd *top)
{
	if (data == NULL)
	{
		free(tk);
		free(tk->data);
		all_free(top);
		printf("minishell:syntax error\n");
		put_exit(SYNTAX_ERROR_EXIT);
		return (1);
	}
	return (0);
}

int	rederiction_handle(t_comm *red, t_tkn *tkn, t_top_cmd *top)
{
	if (syntax_handle(tkn->data, tkn, top) == 1)
		return (1);
	else if (tkn->tkn == T_HEREDOC)
		redirection_add(red->heredoc, tkn);
	else
		redirection_add(red->redirection, tkn);
	return (0);
}