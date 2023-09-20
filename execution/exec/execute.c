/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:42:01 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/20 23:36:59 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../execution.h"
// int	check_builtins(char *cmd)
// {
// 	if (cmd && (ft_strcmp(cmd, "export") == 0))
// 		return (1);
// 	else if (cmd && (ft_strcmp(cmd, "unset") == 0))
// 		return (1);
// 	else if (cmd && (ft_strcmp(cmd, "pwd") == 0))
// 		return (1);
// 	else if (cmd && (ft_strcmp(cmd, "exit") == 0))
// 		return (1);
// 	else if (cmd && (ft_strcmp(cmd, "cd") == 0))
// 		return (1);
// 	else if (cmd && (ft_strcmp(cmd, "env") == 0))
// 		return (1);
// 	else if (cmd && (ft_strcmp(cmd, "echo") == 0))
// 		return (1);
// 	return (0);
// }


// void    execute_cmd(char *cmd, struct Node* head, char *add_key, char *add_val)
// {
//     if (cmd && (ft_strcmp(cmd, "export") == 0))
// 		ft_ex_port(head, add_key, add_val);
// 	else if (cmd && (ft_strcmp(cmd, "unset") == 0))
// 	{
// 		(void)add_val;
// 	    un_set(head, add_key);
// 	}
// 	else if (cmd && (ft_strcmp(cmd, "pwd") == 0))
// 		return ;
// 	else if (cmd && (ft_strcmp(cmd, "exit") == 0))
// 		return ;
// 	else if (cmd && (ft_strcmp(cmd, "cd") == 0))
// 		return ;
// 	else if (cmd && (ft_strcmp(cmd, "env") == 0))
// 	{
// 		(void)add_key;
// 		(void)add_val;
// 		displayList(head);
// 	}
// 	else if (cmd && (ft_strcmp(cmd, "echo") == 0))
// 		return ;
// 	return ;
// }

int execute_cmd(char **env, char *input, struct Node* head, t_cmd *my_cmd)
{
    if (strcmp(input, "exit") == 0) {
        free(input);
        printf("exit\n");
        exit(0);
        return (1);
    }
    else if (strcmp(input, "echo") == 0) {
        e_cho(my_cmd->txt, my_cmd->flag);
        return (1);
    }
    else if(strcmp(input, "env") == 0) {
        displayList(head);
        return (1);
    }
    else if(strcmp(input, "pwd") == 0) {
        pwd();
        return (1);
    }
    else if(strcmp(input, "cd") == 0) {
        cd(env, head);
        return (1);
    }
    else if(strcmp(my_cmd->arguments[0], "export") == 0
        && strcmp(input, "export") == 0) {
            if (fork() == 0)
            {
                ft_ex_port(head,  my_cmd->arguments[1],  my_cmd->arguments[2], env);
            }
            return (1);
        // printf("my_cmd->arguments[0] = %s\n", my_cmd->arguments[1]);
    }
    else if(strcmp(my_cmd->arguments[0], "unset") == 0
        && strcmp(input, "unset") == 0) {
        // printf("my_cmd->arguments[0] = %s\n", my_cmd->arguments[1]);
            if (fork() == 0)
            {
                un_set(head, my_cmd->arguments[1]);
                }
                return (1);
    }
    return (0);
}

void    execute(void)
{
    

}



int main(int ac, char **av, char **env)
{

    (void)ac;
    (void)av;
    (void)env;
    // Create a t_cmd struct
    t_cmd my_cmd;

    /// part get path
    t_path *p = malloc(sizeof(p));
    char* path = getenv("PATH");
	get_path(path, p);

    // Example values
    char *command[] = {"ls", NULL, NULL};
    char *arguments[] = {"export", "ggggg"};
    char *flag = "-n";
    int count = 3;
    int fpipe = 0;
    int rpipe = 0;
    char *text[] = {"yassine", "dddddddd"};

    my_cmd.cmd = (char**)malloc((count + 1) * sizeof(char*));  // +1 for NULL terminator

    my_cmd.cnt = count;
    my_cmd.fpipe = fpipe;
    my_cmd.rpipe = rpipe;
    my_cmd.txt = text;
    my_cmd.flag = flag;
    my_cmd.cmd = command;
    my_cmd.arguments = arguments;

    rl_initialize();

    struct Node* head = NULL;
    // create_env(env, &head);
    // displayList(head);
    create_env(env, &head);
    

    int bl = 0;
    while (1) 
    {
        char *input = readline("minishell$ ");
    
        add_history(input);
        bl = execute_cmd(env, input, head, &my_cmd);
        if(bl == 0)
        {
            int j = 0;
            char *str_join;
            if (my_cmd.rpipe == 0 && my_cmd.fpipe == 0)
            {
                if (fork() == 0)
                {
                    while (j <= p->cnt)
                    {
                    str_join = ft_strjoin(p->path[j], "/");
                    str_join = ft_strjoin(str_join, my_cmd.cmd[0]);
                    // printf("---> %s\n", str_join);
                    execve(str_join, my_cmd.cmd, NULL);
                    if (j == p->cnt)
                    {
                        printf("minishell$ command not found\n");
                        exit(0);
                    }
                    j++;
                    }
                }
            }
            if (my_cmd.fpipe == 1 && my_cmd.rpipe == 0)
            {
                char *arguments11[][3] = {
                 {"ls", "-l", NULL},
                {"wc", "-l", NULL}
                };
                printf("------- test 1----------\n");
                int pipe_fd[2];
                // Create a pipe
                if (pipe(pipe_fd) == -1) {
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }

                // First fork to create the first child process
                pid_t child_pid1 = fork();
                if (child_pid1 == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }

                if (child_pid1 == 0) {
                    // Child process 1
                    dup2(pipe_fd[0], 0);
                    close(pipe_fd[0]); // Close the read end of the pipe
                    j = 0;
                    close(pipe_fd[1]); // Close the read end of the pipe
                    while (j <= p->cnt)
                    {
                        str_join = ft_strjoin(p->path[j], "/");
                        str_join = ft_strjoin(str_join, arguments11[1][0]);
                        // printf(" %s\n ", str_join);
                        execve(str_join, arguments11[1], NULL);
                        j++;
                    }
                    perror("execve");
                    exit(EXIT_FAILURE);
                } else
                {	// Parent process
                    // Second fork to create the second child process
                    pid_t child_pid2 = fork();

                    if (child_pid2 == -1) {
                        perror("fork");
                        exit(EXIT_FAILURE);
                    }

                    if (child_pid2 == 0)
                    {
                        // Child process 2

                        // Redirect stdin to the read end of the pipe
                        dup2(pipe_fd[1], 1);
                        close(pipe_fd[1]); // Close the write end of the pipe
                        close(pipe_fd[0]);
                        j = 0;
                        while (j <= p->cnt)
                        {
                            str_join = ft_strjoin(p->path[j], "/");
                            str_join = ft_strjoin(str_join, arguments11[0][0]);
                            // printf(" %s\n ", str_join);
                            execve(str_join, arguments11[0], NULL);
                            j++;
                        }

                        // This code will only run if execve fails
                        perror("execve");
                        exit(EXIT_FAILURE);
                    } else {
                        // Parent process

                        // Close the pipe file descriptors
                        close(pipe_fd[0]);
                        close(pipe_fd[1]);

                        // Wait for both child processes to complete
                        wait(NULL);
                    }
                }
                printf("-------end test 1----------\n");
            }
        }
        wait(NULL);
        free(input);
    }

    // rl_cleanup(); // This should work without warnings now

    // (void)env;
    //     char *str;
    // while (1)
    // {
    //     readline(str);
    // }
    // printf("%s\n", str);
    // exit(1);
    // execute();
    // printf("dddd");

    // char *str = "ls | ";

    
    // t_env   *e = malloc(sizeof(t_env));
    
    // // displayList(head);

    // printf("*********************************\n");
    // displayList(head);
    // ft_ex_port(head, "fffff",  "ssssssss");
    // printf("+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-\n");
    // displayList(head);
    // un_set(head, "fffff=");
    // // un_set(head, "USER=");

    // // un_set(head, "TERM=");
    //     // displayList_export(head);
    
    // printf("--------------------------------\n");
    // displayList(head);

    // // free(env);
    // free(e);
    
    // free(e->key);
    // free(e->val);
    return 0;
}




