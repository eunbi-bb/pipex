#include "../includes/pipex.h"

void	*protec(void *ptr)
{
	if (ptr == NULL)
		exit(1);
	return (ptr);
}

static char	*string_concat(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		i++;
	}
	j = 0;
	while (s2[j])
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
		if (new_args[new_arg_index] && new_args[new_arg_index][0])
		{
			string_concat(new_args[new_arg_index], " ");
			string_concat(new_args[new_arg_index], args[i]);
			if (args[i][ft_strlen(args[i]) - 1] == '\'')
			{
				new_args[new_arg_index] = protec(ft_substr(new_args[new_arg_index], 1, ft_strlen(new_args[new_arg_index]) - 2));
				new_arg_index++;
			}
		}
		else
		{
			new_args[new_arg_index] = protec(ft_strdup(args[i]));
			if (new_args[new_arg_index][0] != '\'')
				new_arg_index++;
		}
		i++;
	}
	new_args[new_arg_index + 1] = NULL;
}

// (if == \')
// {
// 	i++;
// 	(while != \')
// 		i++;
// }

// ls -l | echo "i wanna be a rockstar"
// 556336765555699999999999999999999999

// while == 
// 	++;
// make list
// num = str[i];



// space = 6
// cmd = 5
// cmd_option = 3
// pipe = 7
// dub_quote = 9
