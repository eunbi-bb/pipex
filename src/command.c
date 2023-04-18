/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:17 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/18 12:06:18 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_cmd_dirs(char **envp)
{
	char	*tmp;
	char	**dirs;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	tmp = *envp + 5;
	dirs = ft_split(tmp, ':');
	return (dirs);
}

char	*command_check(char **path, char *cmd)
{
	char	*command;
	char	*tmp;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		if (command == NULL)
		{
			free(tmp);
			exit(EXIT_FAILURE);
		}
		if (!access(command, X_OK))
		{
			return (command);
		}
		path++;
		free(tmp);
		free(command);
	}
	return (NULL);
}
