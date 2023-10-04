/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:06:12 by hben-mes          #+#    #+#             */
/*   Updated: 2023/10/03 23:06:12 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	syntax_handle(char *val, t_tkn *tkn, t_top_cmd *top)
{
	if (val == NULL)
	{
		free(tkn);
		free(tkn->val);
		all_free(top);
		printf("minishell:syntax error\n");
		put_exit(SYNTAX_ERROR_EXIT);
		return (1);
	}
	return (0);
}
