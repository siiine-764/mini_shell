#include "../minishell_copy.h"

char	*join_for_echo(char **s, char flag)
{
	int		i;
	char	*result;
	char	*temp;

	if (flag == 'n')
		i = 2;
	else
		i = 1;
	result = ft_strdup("");
	while (check_echo_flag(s[i]))
		i++;
	while (s[i])
	{
		temp = result;
		result = ft_strjoin(result, s[i]);
		free(temp);
		result = check_for_space(s, result, i);
		i++;
	}
	return (result);
}
