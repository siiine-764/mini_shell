/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:29:11 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/01 16:30:05 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void ft_close1(int pipes[][2], int i)
{
    dup2(pipes[i - 1][0], STDIN_FILENO);
    close(pipes[i - 1][0]);
}

void ft_close3(int i, int cnt_pipe, int pipes[][2])
{
    if (i > 0)
        close(pipes[i - 1][0]);
    if (i < cnt_pipe - 1)
        close(pipes[i][1]);
}

void    my_execve(char *file, char *args[], t_path *p)
{
    char *str_join = malloc(sizeof(char *));
    int j = 0;

    while (j <= p->cnt)
    {
        str_join = ft_strjoin(p->path[j], "/");
        str_join = ft_strjoin(str_join, file);
        // printf(" %s\n ", str_join);
        execve(str_join, &args[0], NULL);
        j++;
    }
    perror("execve");
    exit(EXIT_FAILURE);
}

void run_pipe(int i, t_cmd *my_cmd, t_path *p)
{
    my_execve(my_cmd->arguments[i][0], my_cmd->arguments[i], p);
    perror("my_execve");
    exit(EXIT_FAILURE);
}