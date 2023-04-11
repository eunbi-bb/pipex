/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:17 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/11 20:09:51 by eucho         ########   odam.nl         */
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
		if (!access(command, X_OK))
		{
			free(tmp);
			return (command);
		}
		path++;
		free(command);
	}
	return (NULL);
}
