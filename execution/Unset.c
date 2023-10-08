#include "../minishell.h"

// t_env	*delete_head(t_env **env_list, char *command, char *del)
// {
// 	t_env	*temp;

// 	// command[0] = "MallocNanoZone";
// 	// printf("command %s\n", command[0]);
// 	// printf("command %s\n", del);
// 	if (ft_strcmp(command, del) == 0)
// 	{
// 		temp = *env_list;
// 		*env_list = (*env_list)->nxt;
// 		free(temp->ctt);
// 		free(temp);
// 		// free(command);
// 		set_exit_code(EXIT_SUCCESS);
// 		return (*env_list);
// 	}
// 	return (NULL);
// }

void deleteNode(t_env **env_list, char* key)
{
    t_env *temp = *env_list;
    t_env *prev = NULL;

	char *str = find_env(*env_list, key);
	if (!str)
	{
		perror("error");
		return ;
	}
	key = ft_strjoin(key, "=");
	key = ft_strjoin(key, str);
	if (temp != NULL && ft_strcmp(temp->ctt, key) == 0)
	{
		*env_list = temp->nxt;
		free(temp);
		return;
	}
	while (temp != NULL && ft_strcmp(temp->ctt, key) != 0)
	{
		prev = temp;
		temp = temp->nxt;
	}
	if (temp == NULL)
		return;
	prev->nxt = temp->nxt;
	free(temp);
	return;
}

void	delete_body(t_info *data)
{
	data->temp = data->sec;
	free_2d(data->command);
	data->fst->nxt = data->sec->nxt;
	free(data->temp->ctt);
	free(data->temp);
}

void	ft_unset(t_env **env_list, char *del)
{
	// t_env	*top;
	(void)del;
	// t_info	data;

	if (!*env_list)
		return ;
	deleteNode(env_list, del);
	// data.fst = *env_list;
	// data.command = ft_split((*env_list)->ctt, '=');
	// if (data.command[0] == NULL)
	// 	return ;
	// else
	// {
	// 	while (env_list)
	// 	{
	// 		if(ft_strcmp((*env_list)->ctt, del) == 0)
	// 		{
	// 			printf("%s\n", (*env_list)->ctt);
	// 			// top = delete_head(env_list, data.command, del);
	// 			// if (top != NULL)
	// 			// 	return ;
	// 		}
	// 		(*env_list) = (*env_list)->nxt;
	// 	}
	// }

	// top = delete_head(env_list, "PATH", del);
	// if (top != NULL)
	// 	return ;
	// if (data.fst == NULL)
	// 	data.sec = data.fst->nxt;
	// else
	// {
		// top = delete_head(env_list, data.command, del);
		// if (top != NULL)
		// 	return ;
		// ft_putendl_fd("IAM HERE LOL", 2);
		// return ;
	// }
	// while (data.sec)
	// {
	// 	free_2d(data.command);
	// 	data.command = ft_split(data.sec->ctt, '=');
	// 	printf("%s\n", data.command[0]);
	// 	if (ft_strcmp(data.command[0], del) == 0)
	// 	{
	// 		delete_body(&data);
	// 		return ;
	// 	}
	// 	data.fst = data.sec;
	// 	data.sec = data.sec->nxt;
	// }
	// free_2d(data.command);
	// set_exit_code(EXIT_SUCCESS);
}

bool	run_unset(t_data *data, t_comm *comm)
{
	int	i;

	if (!ft_strcmp(comm->flags[0], "unset"))
	{
		i = 0;
		while (comm->flags[++i])
		{
			ft_unset(&data->env_list, comm->flags[i]);
			ft_unset(&data->pub_list, comm->flags[i]);
		}
		return (true);
	}
	return (false);
}
