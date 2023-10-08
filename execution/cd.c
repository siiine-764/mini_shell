#include "../minishell.h"

void	cd_oldwd(t_env *env_list, t_env *pub_list)
{
	t_my_data	data;

	getcwd(data.new_wd, sizeof(data.new_wd));
	data.previous_wd = ft_getenv(env_list, "OLDPWD");
	if (!data.previous_wd)
	{
		ft_error("cd", ": OLDPWD NOT FOUND\n", 1);
		return ;
	}
	data.temp = ft_split(data.previous_wd->ctt, '=');
	data.t_path = ft_strdup(data.temp[1]);
	data.i = 0;
	free_2d(data.temp);
	if (chdir(data.t_path) == -1)
	{
		set_exit_code(1);
		perror(data.t_path);
	}
	ft_setenv(&env_list, "OLDPWD", data.new_wd);
	ft_setenv(&pub_list, "OLDPWD", data.new_wd);
	getcwd(data.buff, sizeof(data.buff));
	ft_setenv(&env_list, "PWD", data.buff);
	ft_setenv(&pub_list, "PWD", data.buff);
	free(data.t_path);
	set_exit_code(0);
}

void	cd_home(t_env *env_list, t_env *pub_list)
{
	(void)env_list;
	(void)pub_list;
	// char	*home_path;
	// char	new_wd[PATH_MAX];

	// home_path = find_env(env_list, "HOME");
	// if (home_path == NULL)
	// 	ft_error("cd", " :HOME NOT FOUND", 1);
	// else
	// {
	// 	getcwd(new_wd, sizeof(new_wd));
	// 	if (chdir(home_path) == -1)
	// 	{
	// 		perror(home_path);
	// 		set_exit_code(1);
	// 	}
	// 	else
	// 	{
	// 		ft_setenv(&env_list, "OLDPWD", new_wd);
	// 		ft_setenv(&pub_list, "OLDPWD", new_wd);
	// 		set_exit_code(0);
	// 	}
	// }
	// free(home_path);
	char *a = getenv("HOME");
    if (a == NULL)
    {
        perror("cd :HOME NOT FOUND");
        return ;
    }
	chdir(a);
}


// void	cd_home(struct Node* head, char **env)
// {
//     (void)head;
//     (void)env;

//     char *a = getenv("HOME");
//     if (a == NULL)
//     {
//         perror("cd :HOME NOT FOUND");
//         return ;
//     }
//     else
//     {
//         ft_ex_port(head, "PWD", a, env);
//         printf("im here\n");
//     }
//     chdir(a);
// }

void	ft_cd(t_comm *comm, char *path, t_env *env_list, t_env *pub_list)
{
	(void)pub_list;
	// char	new_wd[PATH_MAX];

	// if (ft_strcmp("-", path) == 0)
	// 	cd_oldwd(env_list, pub_list);
	// else 
	if (path == NULL)
		cd_home(env_list, pub_list);
	else if (ft_strcmp(".", path) == 0)
	{
		return ;
		// cd_home(env_list, pub_list);
	}
	else if (ft_strcmp("..", path) == 0)
	{
        ft_export(comm, pub_list, "OLDPWD");
        chdir("..");
        return ;
		// cd_home(env_list, pub_list);
	}
	else
	{
		// chdir(path);
		if (chdir(path) == -1)
		{
			set_exit_code(1);
			perror(path);
		}
		// getcwd("PWD", sizeof("PWD"));
		ft_export(comm, pub_list, "OLDPWD");
		// else
		// {
		// 	set_exit_code(0);
		// 	ft_setenv(&env_list, "OLDPWD", new_wd);
		// }
	}
}

bool	run_cd(t_data data, t_comm *comm)
{
	(void)data;
	if (!ft_strcmp(comm->flags[0], "cd"))
	{
		ft_cd(comm, comm->flags[1], data.env_list, data.pub_list);
		return (true);
	}
	return (false);
}
