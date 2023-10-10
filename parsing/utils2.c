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

int	syntax_handle(char *val, t_tkn *t, t_top_cmd *top)
{
	(void)t;
	if (val == NULL)
	{
		// free(t);
		free(t->val);
		all_free(top);
		printf("minishell:syntax error\n");
		set_exit_code(SYNTAX_ERROR_EXIT);
		return (1);
	}
	return (0);
}
