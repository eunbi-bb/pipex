#include "../includes/pipex.h"

static char	*string_concat(char s1[], char s2[])
{
	int i = 0;
	int j = 0;

	while (s1[i] != '\0')
	{
		i++;
	}
	while (s2[j] != '\0')
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

void	multiple_args(t_pipex *pipex, char **args, char **new_args)
{
	int		i;
	int		new_arg_index;
	int		keep_reading;

	new_arg_index = 0;
	keep_reading = 0;
	i = 0;
	while (args[i])
	{
		if (keep_reading == 1)
		{
			if (new_args[new_arg_index][ft_strlen(new_args[new_arg_index]) - 1] != '\'')
				string_concat(new_args[new_arg_index], " ");
			string_concat(new_args[new_arg_index], args[i]);
		}
		else
			new_args[new_arg_index] = ft_strdup(args[i]);
		if (args[i][0] == '\'')
		{
			keep_reading = 1;
			new_args[new_arg_index] = ft_substr(new_args[new_arg_index], 1, ft_strlen(new_args[new_arg_index]));
		}
		if (args[i][ft_strlen(args[i]) - 1] == '\'')
		{
			keep_reading = 0;
			new_args[new_arg_index] = ft_substr(new_args[new_arg_index], 0, ft_strlen(new_args[new_arg_index]) - 1);
		}
		if (keep_reading == 0)
			new_arg_index++;
		free (args[i]);
		i++;
	}
	new_args[new_arg_index + 1] = '\0';
	pipex->cmd_args = new_args;
}