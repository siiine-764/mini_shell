/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:32:51 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/25 23:49:49 by mayache-         ###   ########.fr       */
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


char *ft_redir_herdoc(t_cmd *my_cmd, char *delimiter)
{
    (void)my_cmd;
    (void)delimiter;
    char *heredocInput = NULL;
    size_t heredocInputSize = 0;

    while (1) {
        char *line = readline(">"); // Use readline instead of getline

        if (line == NULL) {
            perror("Error reading input");
            free(heredocInput);
            return NULL;
        }

        if (strcmp(line, "END") == 0) {
            free(line);
            break;
        }
        add_history(line); // Add the line to history
        size_t lineLength = strlen(line);
        heredocInput = realloc(heredocInput, heredocInputSize + lineLength + 1);
        if (heredocInput == NULL) {
            perror("Memory allocation failed");
            free(line);
            return NULL;
        }
        memcpy(heredocInput + heredocInputSize, line, lineLength);
        heredocInputSize += lineLength;
        heredocInput[heredocInputSize] = '\n'; // Add newline character

        free(line);
    }

    if (heredocInputSize > 0) {
        heredocInput[heredocInputSize] = '\0';
    } else {
        perror("No input provided");
        free(heredocInput);
        return NULL;
    }

    return heredocInput;
}

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
//     if (my_cmd->redir->typ_redir == 120)
//     {
//         printf("here doc\n");
//     }
// }