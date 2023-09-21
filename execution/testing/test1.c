// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// int main() {
//     int pipe_fd[2];  // Pipe file descriptors for communication between processes
//     char *wc_args[] = {"/usr/bin/wc", "-l", NULL};
//     char *ls_args[] = {"/bin/ls", "-l", NULL};
//     // Create a pipe
//     if (pipe(pipe_fd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     // First fork to create the first child process
//     pid_t child_pid1 = fork();

//     if (child_pid1 == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (child_pid1 == 0) {
//         // Child process 1

//         dup2(pipe_fd[0], 0);
//         close(pipe_fd[0]); // Close the read end of the pipe
//         close(pipe_fd[1]);
//         // Execute the command "/usr/bin/wc -l"
//         execve("/usr/bin/wc", wc_args, NULL);

//         // This code will only run if execve fails
//         perror("execve");
//         exit(EXIT_FAILURE);
//     } else {
//         // Parent process

//         // Second fork to create the second child process
//         pid_t child_pid2 = fork();

//         if (child_pid2 == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }

//         if (child_pid2 == 0) {
//             // Child process 2

//             // Redirect stdin to the read end of the pipe
//             dup2(pipe_fd[1], 1);
//             close(pipe_fd[1]); // Close the write end of the pipe
//             close(pipe_fd[0]);
//             // Execute the command "/bin/ls -l"
//             char *ls_args[] = {"/bin/ls", "-l", NULL};
//             execve("/bin/ls", ls_args, NULL);

//             // This code will only run if execve fails
//             perror("execve");
//             exit(EXIT_FAILURE);
//         } else {
//             // Parent process

//             // Close the pipe file descriptors
//             close(pipe_fd[0]);
//             close(pipe_fd[1]);

//             // Wait for both child processes to complete
//             wait(NULL);
//         }
//     }

//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// // extern void rl_cleanup(void); // Declaration for rl_cleanup
// int main() {
    
//     rl_initialize();

//     while (1) {
//         char *input = readline("minishell$ ");

//         if (strcmp(input, "exit") == 0) {
//             free(input);
//             break;
//         }

//         add_history(input);
//         printf("You entered: %s\n", input);
//         free(input);
//     }

//     // rl_cleanup(); // This should work without warnings now

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


// void my_execvp(const char *file, char *const args[], t_path *p) {
//     // Attempt to execute the specified file with arguments
//     execve(file, args, NULL);

//     // If execve fails, print an error message and exit
//     perror("execve");
//     exit(EXIT_FAILURE);
// }



int main() {
    char *arguments11[][3] = {
        // {"ls", "-l", NULL},
        // {"wc", "-l", NULL},
        // {"grep", "main_ex.c", NULL},
        // {"sort", NULL, NULL},
        {"cat", "main_ex.c", NULL},
        {"grep", "printf", NULL},
        {"sort", NULL, NULL},
        {"uniq", NULL, NULL},
        // ls -l | grep "myfile" | sort
        // cat main_ex.c | grep "keyword" | sort | uniq

    };

        int num_commands = sizeof(arguments11) / sizeof(arguments11[0]);

        // printf("num_commands: %d\n", num_commands);
        // Create pipes for connecting commands
        int pipes[num_commands - 1][2];

        int i = 0;
        while (i < num_commands)
        {
            if (pipe(pipes[i]) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            i++;
        }

        i = -1;
        // Execute commands and connect them with pipes
        while (++i < num_commands)
        {
            pid_t pid = fork();

            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) {
                // Child process
                if (i > 0) {
                    // Connect input to the previous pipe
                    dup2(pipes[i - 1][0], STDIN_FILENO);
                    close(pipes[i - 1][0]);
                }

                if (i < num_commands - 1) {
                    // Connect output to the current pipe
                    dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][1]);
                }

                // Execute the command
                // my_execvp(arguments11[i][0], arguments11[i]);
                execvp(arguments11[i][0], arguments11[i]);
                perror("my_execvp");
                exit(EXIT_FAILURE);
            } else {
                // Parent process
                if (i > 0) {
                    close(pipes[i - 1][0]);
                }
                if (i < num_commands - 1) {
                    close(pipes[i][1]);
                }
            }
        }

        // Wait for all child processes to finish
        int j = 0;
        while (j < num_commands)
        {
            wait(NULL);
            j++;
        }
        // Close any remaining open pipes
        j = 0;
        while (j < num_commands)
        {
            close(pipes[j][0]);
            close(pipes[j][1]);
            j++;
        }

    return 0;
}
