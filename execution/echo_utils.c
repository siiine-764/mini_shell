#include "../minishell.h"

char	*join_for_echo(char **str, char flag)
{
	int		i;
	char	*j;
	char	*res;
	
	if (flag == 'n')
		i = 2;
	else
		i = 1;
	res = ft_strdup("");
	while (check_echo_flag(str[i]))
		i++;
	while (str[i])
	{
		j = res;
		res = ft_strjoin(res, str[i]);
		free(j);
		res = check_for_space(str, res, i);
		i++;
	}
	return (res);
}
