

#include "../MiniShell.h"

void	free_2d_array(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
}

void	free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->content);
		free(temp);
		temp->content = NULL;
		temp = NULL;
	}
}
