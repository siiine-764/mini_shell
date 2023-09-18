# include "../execution.h"

int	check_builtins(char *cmd)
{
	if (cmd && (ft_strcmp(cmd, "export") == 0))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "unset") == 0))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "pwd") == 0))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "exit") == 0))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "cd") == 0))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "env") == 0))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "echo") == 0))
		return (1);
	return (0);
}


void    execute_cmd(char *cmd, struct Node* head, char *add_key, char *add_val)
{
    if (cmd && (ft_strcmp(cmd, "export") == 0))
		ft_ex_port(head, add_key, add_val);
	else if (cmd && (ft_strcmp(cmd, "unset") == 0))
	{
		(void)add_val;
	    un_set(head, add_key);
	}
	else if (cmd && (ft_strcmp(cmd, "pwd") == 0))
		return ;
	else if (cmd && (ft_strcmp(cmd, "exit") == 0))
		return ;
	else if (cmd && (ft_strcmp(cmd, "cd") == 0))
		return ;
	else if (cmd && (ft_strcmp(cmd, "env") == 0))
	{
		(void)add_key;
		(void)add_val;
		displayList(head);
	}
	else if (cmd && (ft_strcmp(cmd, "echo") == 0))
		return ;
	return ;
}

// void    execute(void)
// {
//     if (check_builtins(CMD) == 1)
//     {
//         printf("erorr\n");
//     }

// }

