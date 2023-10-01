/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:27:06 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/01 16:29:53 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

// 1 write 
// 0 read

void    pi_pe(t_cmd *my_cmd, t_path *p)
{
    pid_t pid;
    int i;
    int pipes[my_cmd->cnt_pipe - 1][2];

    ft_error2(my_cmd->cnt_pipe, pipes);
    i = -1;
    while (++i < my_cmd->cnt_pipe)
    {
        pid = fork();
        check_pid_error(pid);
        if (pid == 0)
        {
            if (i > 0)
                ft_close1(pipes, i);
            if (i < my_cmd->cnt_pipe - 1)
                ft_close2(pipes, i);
            run_pipe(i, my_cmd, p);
        }
        else
            ft_close3(i, my_cmd->cnt_pipe, pipes);
    }
    wait_all(my_cmd->cnt_pipe);
}
