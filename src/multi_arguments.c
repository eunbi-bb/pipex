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

void	multiple_args(char **args, char **new_args)
{
	int		i;
	int		new_arg_index;

	new_arg_index = 0;
	i = 0;
	while (args[i])
	{
		if (new_args[new_arg_index] && new_args[new_arg_index][0] == '\'')
		{
			string_concat(new_args[new_arg_index], " ");
			string_concat(new_args[new_arg_index], args[i]);
			if (args[i][ft_strlen(args[i]) - 1] == '\'')
			{
				new_args[new_arg_index] = ft_substr(new_args[new_arg_index], 1, ft_strlen(new_args[new_arg_index]) - 2);
				new_arg_index++;
			}
		}
		else
		{
			new_args[new_arg_index] = ft_strdup(args[i]);
			if (new_args[new_arg_index][0] != '\'')
				new_arg_index++;
		}
		i++;
	}
	new_args[new_arg_index + 1] = '\0';
}