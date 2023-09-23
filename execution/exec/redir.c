/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:32:51 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/22 23:53:29 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// void ft_redirect_output(char *file, t_path *p, t_cmd *my_cmd)
// {
//     // open() returns a file descriptor file_desc to the file specified in argv[1]
//     int file_desc = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
//     if (file_desc == -1)
//     {
//         perror("test");
//         return;
//     }
//     int old_fd = dup(1);
    
//     // Use dup2 to duplicate file_desc to copy_desc
//     int copy_desc = dup2(file_desc, STDOUT_FILENO);
//     excute_cmd(my_cmd, p);
//     close(copy_desc);
//     dup2(old_fd, STDOUT_FILENO);
//     close(file_desc);
//     (void)p;
//     (void)my_cmd;
// }

// void ft_redirect_input(char *file, t_path *p, t_cmd *my_cmd)
// {
//     // open() returns a file descriptor file_desc to the file specified in argv[1]
//     int file_desc = open(file, O_RDONLY | O_CREAT , 0777);
//     if (file_desc == -1)
//     {
//         perror("test");
//         return;
//     }
//     int old_fd = dup(0);
//     // Use dup2 to duplicate file_desc to copy_desc
//     int copy_desc = dup2(file_desc, STDIN_FILENO);
//     excute_cmd(my_cmd, p);
//     close(copy_desc);
//     dup2(old_fd, STDIN_FILENO);
//     close(file_desc);
//     (void)p;
//     (void)my_cmd;
// }

// void ft_redirect_output_append(char *file, t_path *p, t_cmd *my_cmd)
// {
//     // open() returns a file descriptor file_desc to the file specified in argv[1]
//     int file_desc = open(file, O_RDONLY | O_APPEND | O_CREAT , 0777);
//     if (file_desc == -1)
//     {
//         perror("test");
//         return;
//     }
//     int old_fd = dup(1);
//     // Use dup2 to duplicate file_desc to copy_desc
//     int copy_desc = dup2(file_desc, STDOUT_FILENO);
//     if (copy_desc == -1)
//     {
//         perror("test");
//         return;
//     }
//     excute_cmd(my_cmd, p);
//     close(copy_desc);
//     dup2(old_fd, STDOUT_FILENO);
//     close(file_desc);
//     (void)p;
//     (void)my_cmd;
// }

// void ft_redir(t_cmd *my_cmd, t_path *p)
// {
//     if (my_cmd->redir->typ_redir == 62)
//     {
//         printf("out\n");
//         ft_redirect_output(my_cmd->redir->file, p, my_cmd);
//     }
//     else if (my_cmd->redir->typ_redir == 60)
//     {
//         printf("in\n");
//         ft_redirect_input(my_cmd->redir->file, p, my_cmd);
//     }
//     else if(my_cmd->redir->typ_redir == 124)
//     {
//         printf("out append\n");
//         ft_redirect_output_append(my_cmd->redir->file, p, my_cmd);
//     }
//     // if (my_cmd->redir->typ_redir == 120)
//     // {
//     //     printf("120");
//     // }
// }