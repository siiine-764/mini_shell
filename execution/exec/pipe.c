# include "../execution.h"

// 1 write 
// 0 read

// Wait for all child processes to finish
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

void    my_execve(char *file, char *args[], t_path *p) {
    char *str_join;
    int j = 0;

    // Attempt to execute the specified file with arguments
    while (j <= p->cnt)
    {
        str_join = ft_strjoin(p->path[j], "/");
        str_join = ft_strjoin(str_join, file);
        // printf(" %s\n ", str_join);
        execve(str_join, &args[0], NULL);
        j++;
    }
    // If execve fails, print an error message and exit
    perror("execve");
    exit(EXIT_FAILURE);
}

void    pi_pe(t_cmd *my_cmd, t_path *p)
{
    char *arguments11[][3] = {
        // {"echo", "'Hello, World'", NULL},
        // {"echo", "'Hello, World'", NULL},
        // {"echo", "'Hello, World'", NULL},
        // {"grep", "Hello", NULL},
        {"ls", "-l", NULL},
        {"wc", "-l", NULL},
        // {"grep", "main_ex.c", NULL},
        // {"sort", NULL, NULL},
        // {"cat", "./testing/main_ex.c", NULL},
        // {"grep", "printf", NULL},
        // {"sort", NULL, NULL},
        // {"uniq", NULL, NULL},
        // ls -l | grep "myfile" | sort
        // cat main_ex.c | grep "keyword" | sort | uniq
    };

    // Create pipes for connecting commands
    int pipes[my_cmd->cnt_pipe - 1][2];

    // Create pipes for connecting commands
    int i = -1;
    while (++i < my_cmd->cnt_pipe)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    i = -1;
    // Execute commands and connect them with pipes
    while (++i < my_cmd->cnt_pipe)
    {
        pid_t pid = fork();
        check_pid_error(pid);
        if (pid == 0) {
            // Child process
            if (i > 0) {
                // Connect input to the previous pipe
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i - 1][0]);
            }
            if (i < my_cmd->cnt_pipe - 1)
            {
                // Connect output to the current pipe
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][1]);
            }
            // Execute the command
            my_execve(arguments11[i][0], arguments11[i], p);
            perror("my_execve");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            if (i > 0)
                close(pipes[i - 1][0]);
            if (i < my_cmd->cnt_pipe - 1)
                close(pipes[i][1]);
        }
    }
    // Wait for all child processes to finish
    wait_all(my_cmd->cnt_pipe);
    // Close any remaining open pipes
    // int j = 0;
    // while (j < my_cmd->cnt_pipe)
    // {
    //     close(pipes[j][0]);
    //     close(pipes[j][1]);
    //     j++;
    // }
}
