/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:42:01 by mayache-          #+#    #+#             */
/*   Updated: 2023/10/01 16:48:14 by mayache-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// int	check_builtins(char *cmd)
// {
// 	if (cmd && (ft_strcmp(cmd, "export") == 0))
// 		return (1);
// 	else if (cmd && (ft_ft_strcmp(cmd, "unset") == 0))
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

t_path    *get_path(char *path)
{
    int i;
    i = 0;

    t_path *p;

    p = ft_calloc (1, sizeof(t_path));
    p->path = ft_split(path, ':');
    while (p->path[i])
    {
        p->cnt++;
        // printf("*** %s ***\n", p->path[i]);
        i++;
    }
    return (p);
}

int    run_builtins0(char *input, struct Node* head, char **env, t_cmd *my_cmd)
{ 
    // (void)my_cmd;
    if (ft_strcmp(input, "exit") == 0)
    {
        // free(input);
        // ex_it();
        // printf("0\n");
        return (2);
    }
    else if(ft_strcmp(input, "pwd") == 0)
    {
        // printf("1\n");
        pwd();
        return ( 1);
    }
    else if(ft_strcmp(input, "cd") == 0)
    {
        // printf("2\n");
        cd(env, head, my_cmd);
        return ( 1);
    }
    else if(ft_strcmp(input, "env") == 0)
    {
        // printf("3\n");
        displayList(head);
        return ( 1);
    }
    return ( 0);
}

int run_builtins1(t_cmd *my_cmd, char **env, char *input, struct Node* head)
{
    int i;

    i = -1;
    while (++i < 2)
    {
        if(ft_strcmp(my_cmd->arguments[i][0], "export") == 0
        && ft_strcmp(input, "export") == 0)
        {
            if (fork() == 0)
            {
                ft_ex_port(head,  my_cmd->arguments[i][1],  my_cmd->arguments[i][2], env);
            }
            wait(NULL);
            return (1);
        }
    }
    return (0);
}

int run_builtins2(t_cmd *my_cmd, char *input, struct Node* head)
{
    int i;

    i = -1;
    while (++i < 2)
    {
        if(ft_strcmp(my_cmd->arguments[i][0], "unset") == 0
        && ft_strcmp(input, "unset") == 0)
        {
            if (fork() == 0)
            {
                un_set(head, my_cmd->arguments[i][1]);
            }
            wait(NULL);
            return (1);
        }
    }
    return (0);
}
int execute_builtins(char **env, char *input, struct Node* head, t_cmd *my_cmd)
{
    int i;

    i = -1;
    while (++i < 2)
    {
        if (run_builtins0(input, head, env, my_cmd) == 1)
            return (1);
        if (run_builtins0(input, head, env, my_cmd) == 2)
            return (2);
        else if (ft_strcmp(input, "echo") == 0)
        {
            e_cho(my_cmd->arguments[i], my_cmd->flag);
            return (1);
        }
        else if (run_builtins1(my_cmd, env, input, head) == 1)
            return (1);
        else if (run_builtins2(my_cmd, input, head) == 1)
            return (1);
    }
    return (0);
}

void    excute_cmd(t_cmd *my_cmd, t_path *p)
{
    int j;
    char *str_join;

    j = 0;
    if (fork() == 0)
    {
        while (j <= p->cnt)
        {
            str_join = ft_strjoin(p->path[j], "/");
            str_join = ft_strjoin(str_join, my_cmd->arguments[0][0]);
            execve(str_join, &my_cmd->arguments[0][0], NULL);
            if (j == p->cnt)
            {
                printf("minishell$ command not found\n");
                exit(0);
            }
            j++;
        }
    }
    wait(NULL);
}

// void    execute(t_cmd *my_cmd, char **env)
// {
//     char *input;
//     struct Node* head = NULL;
//     t_path *p = malloc(sizeof(p));
//     char* path = malloc(sizeof(char *));
//     path = getenv("PATH");
    
// 	p = get_path(path);
//     create_env(env, &head);
    
//     rl_initialize();
//     int bl = 0;
//     while (1)
//     {
//         input = readline("minishell$ ");
//         add_history(input);
//         bl = execute_builtins(env, input, head, my_cmd);
//         if(bl == 0)
//         {
//             if (my_cmd->pipe == 0 && my_cmd->redir->cnt_redir <= 1)
//             {
//                 printf("redir\n");
//                 ft_redir(my_cmd, p);
//             }
//             // if (my_cmd->pipe == 0)
//             //     excute_cmd(my_cmd, p);
//             // else if (my_cmd->pipe == 1)
//             //     pi_pe(my_cmd, p);
//         }
//         free(input);
//     }
// }

void free_path(t_path *p)
{
    // Free any memory allocated within the t_path struct
    // For example, if there's a dynamically allocated path string:
    // free(p->path);
    
    // Free the t_path struct itself
    free(p);
}

void    excute_cpy(t_cmd *my_cmd, char **env, struct Node* head, char *input)
{
    t_path  *p = malloc(sizeof(p));
    char    *path = malloc(sizeof(char *));
    path = getenv("PATH");

	p = get_path(path);
    // create_env(env, &head);

    int bl = 0;
    bl = execute_builtins(env, input, head, my_cmd);
    if(bl == 0)
    {
        // if (my_cmd->pipe == 0 && my_cmd->redir->cnt_redir <= 1)
        // {
        //     printf("redir\n");
        //     ft_redir(my_cmd, p);
        // }
        if (my_cmd->pipe == 0)
            excute_cmd(my_cmd, p);
        else if (my_cmd->pipe == 1)
            pi_pe(my_cmd, p);
    }
    if (bl == 2)
    {
        free(input);
        free_path(p);
        free(my_cmd);
        // ex_it();
    }
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;

    struct Node* head = NULL;
    create_env(env, &head);
    // my struct
    t_cmd *my_cmd = (t_cmd *)malloc(sizeof(t_cmd));
    
    // for example : //
    
    char *arguments[][3] = 
    {   
        {"ls", "-l"},
        {"grep", "main"},
        // {"sort"},
        // {"uniq"},
        // ls -l | grep "myfile" | sort
        // cat main_ex.c | grep "keyword" | sort | uniq
    };
    
    my_cmd->cnt_pipe = 1;
    my_cmd->pipe = 0;
    my_cmd->flag = "-nnnn";
    if (my_cmd == NULL)
    {
        perror("Memory allocation failed");
        return 1;
    }
    my_cmd->arguments = (char ***)malloc(2 * sizeof(char **));
    if (my_cmd->arguments == NULL)
    {
        perror("Memory allocation failed");
        free(my_cmd);
        return 1;
    }
    for (int i = 0; i < 2; i++)
    {
        my_cmd->arguments[i] = (char **)malloc(3 * sizeof(char *));
        if (my_cmd->arguments[i] == NULL) {
            perror("Memory allocation failed");
            return 1;
        }

        for (int j = 0; j < 3; j++) {
            my_cmd->arguments[i][j] = arguments[i][j];
        }
    }

    // end example //

    // //
    char *input;

    rl_initialize();
    while (1)
    {
        input = readline("minishell$ ");
        add_history(input);
        // my function
        excute_cpy(my_cmd, env, head, input);

        free(input);
    }
    // //

    return 0;
}