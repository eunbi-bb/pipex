/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 12:29:06 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/18 13:10:31 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	array_size(char **args)
{
	int	arg_num;

	if (args == NULL)
		return (0);
	arg_num = 0;
	while (args[arg_num])
		arg_num++;
	return (arg_num);
}

int	new_array_size(char *str)
{
	char	*list;
	char	**tmp;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	list = create_list(str, i, j);
	tmp = ft_split(list, '0');
	size = array_size(tmp);
	return (size);
}

char	*create_list(char *argv, int i, int j)
{
	char	*list;

	list = ft_calloc(sizeof(char), ft_strlen(argv) + 1);
	if (!list)
		return (0);
	while (argv[i])
	{
		if (argv[i] == '\'')
		{
			i++;
			while (argv[i] && argv[i] != '\'')
			{
				list[j++] = '2';
				i++;
			}
		}
		else if (argv[i] == ' ')
			list[j++] = '0';
		else
			list[j++] = '1';
		i++;
	}
	return (list);
}
