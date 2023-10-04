/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:27:44 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/01 16:28:54 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void wait_all(int cnt_pipe)
{
    int j = 0;
    while (j < cnt_pipe)
    {
        wait(NULL);
        j++;
    }
}
void    check_pid_error(pid_t pid)
{
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void ft_close2(int pipes[][2], int i)
{
    dup2(pipes[i][1], STDOUT_FILENO);
    close(pipes[i][1]);
}

void ft_error()
{
    perror("pipe");
    exit(EXIT_FAILURE);
}

void ft_error2(int cnt_pipe, int pipes[][2])
{
    int i;

    i = -1;
    while (++i < cnt_pipe)
        if (pipe(pipes[i]) == -1)
            ft_error();
}