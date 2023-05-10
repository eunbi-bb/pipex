/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_quotation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 12:03:23 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/18 13:10:47 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	single_quotation(char **args, char **new, int size)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (args[i] && j < size)
	{
		new[j] = ft_strdup(args[i]);
		if (new[j][0] != '\'')
			j++;
		if (new[j] && new[j][0] == '\'')
		{
			while (new[j] && new[j][ft_strlen(new[j]) - 1] != '\'')
			{
				i++;
				new[j] = ft_strjoin(new[j], " ");
				new[j] = ft_strjoin(new[j], args[i]);
			}
			if (new[j][ft_strlen(new[j]) - 1] == '\'')
				new[j] = ft_substr(new[j], 1, ft_strlen(new[j]) - 2);
		}
		i++;
	}
	if (new[j] != NULL)
		new[j + 1] = NULL;
}
