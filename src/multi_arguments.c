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
	int	len_1;
	int	len_2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len_1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < len_2)
	{
		str[i++] = s2[j];
		j++;
	}
	str[i] = '\0';
	return (s1);
}

void	multiple_args(char **args, char **new_args)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	printf("new_args[0]: %s\n", new_args[0]);
	while (args[i])
	{
		if (new_args[j] && new_args[j][0] == '\'')
		{
			string_concat(new_args[j], " ");
			string_concat(new_args[j], args[i]);
			if (args[i][ft_strlen(args[i]) - 1] == '\'')
			{
				new_args[j] = ft_substr(new_args[j], 1, ft_strlen(new_args[j]) - 2);
				j++;
			}
		}
		else
		{
			new_args[j] = ft_strdup(args[i]);
			if (new_args[j][0] != '\'')
				j++;
		}
		i++;
	}
	new_args[j + 1] = NULL;
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
