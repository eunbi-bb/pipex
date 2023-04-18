#include "../includes/pipex.h"

void	*protec(void *ptr)
{
	if (ptr == NULL)
		exit(1);
	return (ptr);
}

void	multiple_args(char **args, char **new_args, int new_args_size, t_pipex *pipex)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (args[i] && j < new_args_size)
	{
		new_args[j] = ft_strdup(args[i]);
		if (new_args[j][0] != '\'')
			j++;
		if (new_args[j] && new_args[j][0] == '\'')
		{
			while (new_args[j] && new_args[j][ft_strlen(new_args[j]) - 1] != '\'')
			{
				i++;
				new_args[j] = ft_strjoin(new_args[j], " ");
				new_args[j] = ft_strjoin(new_args[j], args[i]);
			}
			if (new_args[j][ft_strlen(new_args[j]) - 1] == '\'')
				new_args[j] = ft_substr(new_args[j], 1, ft_strlen(new_args[j]) - 2);;
		}
		i++;
	}
	//printf("new_args[%d] : %s\n", j, new_args[j]);
	if (new_args[j] != NULL)
		new_args[j + 1] = NULL;
	pipex->cmd_args = new_args;
	// int n = 0;
	// while (new_args[n])
	// {
	// 	printf("new_args[%d] : %s\n", n, new_args[n]);
	// 	n++;
	// }
}
