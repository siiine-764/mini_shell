/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:32:51 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/18 23:44:22 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "../execution.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    // Redirecting input using '<'
    int input_fd;
    if ((input_fd = open("input.txt", O_RDONLY)) == -1) {
        perror("Error opening input.txt");
        exit(EXIT_FAILURE);
    }
    dup2(input_fd, STDIN_FILENO); // Redirect standard input to input.txt
    close(input_fd);

    // Redirecting output using '>'
    int output_fd;
    if ((output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        perror("Error opening output.txt");
        exit(EXIT_FAILURE);
    }
    dup2(output_fd, STDOUT_FILENO); // Redirect standard output to output.txt
    close(output_fd);

    // Redirecting output in append mode using '>>'
    int append_fd;
    if ((append_fd = open("append.txt", O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1) {
        perror("Error opening append.txt");
        exit(EXIT_FAILURE);
    }
    dup2(append_fd, STDOUT_FILENO); // Redirect standard output to append.txt
    close(append_fd);

    // Reading input until a delimiter using '<<'
    char delimiter[] = "END";
    char buffer[1024];
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        if (strcmp(buffer, delimiter) == 0) {
            break;
        }
        printf("Input: %s", buffer); // Print input until delimiter is seen
    }

    // Restore standard output to the terminal
    dup2(STDOUT_FILENO, STDOUT_FILENO);

    printf("This will be printed to the terminal.\n");

    return 0;
}
