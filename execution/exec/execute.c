/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayache- <mayache-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:42:01 by mayache-          #+#    #+#             */
/*   Updated: 2023/09/22 23:52:29 by mayache-         ###   ########.fr       */
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
            wait(NULL);
            return (1);
    }
    else if(strcmp(my_cmd->arguments[0], "unset") == 0
        && strcmp(input, "unset") == 0) {
            if (fork() == 0)
            {
                un_set(head, my_cmd->arguments[1]);
            }
            wait(NULL);
            return (1);
    }
    return (0);
}

void    excute_cmd(t_cmd *my_cmd, t_path *p)
{
    int j = 0;
    char *str_join;
    if (fork() == 0)
    {
        while (j <= p->cnt)
        {
        str_join = ft_strjoin(p->path[j], "/");
        str_join = ft_strjoin(str_join, my_cmd->cmd[0]);
        // printf("---> %s\n", str_join);
        execve(str_join, my_cmd->cmd, NULL);
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

void    execute(t_cmd *my_cmd, char **env)
{
    char *input;
    struct Node* head = NULL;
    t_path *p = malloc(sizeof(p));
    char* path = malloc(sizeof(char *));
    path = getenv("PATH");
    
	p = get_path(path);
    create_env(env, &head);
    
    rl_initialize();
    int bl = 0;
    while (1)
    {
        input = readline("minishell$ ");
        add_history(input);
        bl = execute_cmd(env, input, head, my_cmd);
        if(bl == 0)
        {
            if (my_cmd->pipe == 0 && my_cmd->redir->cnt_redir <= 1)
            {
                printf("redir\n");
                ft_redir(my_cmd, p);
            }
            // if (my_cmd->pipe == 0)
            //     excute_cmd(my_cmd, p);
            // else if (my_cmd->pipe == 1)
            //     pi_pe(my_cmd, p);
        }
        free(input);
    }
}


int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
    // Create a t_cmd struct
    t_cmd *my_cmd = ft_calloc (1, sizeof(t_cmd));

    // Example values
    char *command[] = {"cat", NULL, NULL};
    char *arguments[] = {"export", "sss", "fffff", NULL};
    char *flag = "-n";
    int count = 3;
    int cnt_pipe = 4;
    int fpipe = 0;
    int rpipe = 0;
    int pp = 0;
    char *text[] = {"yassine", "dddddddd", NULL};

    my_cmd->cmd = (char**)malloc((count + 1) * sizeof(char*));  // +1 for NULL terminator

    my_cmd->cnt = count;
    my_cmd->fpipe = fpipe;
    my_cmd->rpipe = rpipe;
    my_cmd->txt = text;
    my_cmd->flag = flag;
    my_cmd->cmd = command;
    my_cmd->arguments = arguments;
    my_cmd->cnt_pipe = cnt_pipe;
    my_cmd->pipe = pp;

    int typ = 124;
    int cctyp = 0;
    char *sttt =  "file.txt";
    my_cmd->redir = ft_calloc (1, sizeof(t_redir));
    my_cmd->redir->typ_redir = typ;
    my_cmd->redir->cnt_redir = cctyp;
    my_cmd->redir->file = sttt;
    execute(my_cmd, env);
    return 0;
}
