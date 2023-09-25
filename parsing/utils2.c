/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:12:28 by hben-mes          #+#    #+#             */
/*   Updated: 2023/09/25 13:13:10 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniShell.h"

int	exit_code(void)
{
	return (g_global_vars.exit_code);
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

