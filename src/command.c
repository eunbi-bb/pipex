/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:17 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/18 13:42:44 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_cmd_dirs(char **envp)
{
	char	*tmp;
	char	**dirs;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
			break ;
		envp++;
	}
	if (*envp == NULL)
	{
		error_msg("Path cannot be found");
		exit(errno);
	}
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
