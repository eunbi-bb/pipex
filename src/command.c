/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:17 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/20 17:15:10 by eucho         ########   odam.nl         */
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
	if (*envp)
	{
		tmp = *envp + 5;
		dirs = ft_split(tmp, ':');
		return (dirs);
	}
	return (NULL);
}

char	*command_check(char **path, char *cmd)
{
	char	*command;
	char	*tmp;

	if (path == NULL)
		return (NULL);
	if ((access(cmd, X_OK) == 0))
		return (cmd);
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		if (command == NULL)
		{
			free(tmp);
			exit(EXIT_FAILURE);
		}
		if (!access(command, F_OK))
			return (command);
		path++;
		free(tmp);
		free(command);
	}
	return (NULL);
}

void	generate_command(t_pipex *pipex)
{
	pipex->command = command_check(pipex->cmd_dirs, pipex->cmd_args[0]);
	if (pipex->cmd_dirs == NULL && access(pipex->cmd_args[0], X_OK) == 0)
		pipex->command = pipex->cmd_args[0];
	if (pipex->command == NULL)
	{
		cmd_error(pipex->cmd_args[0]);
		free_child(pipex);
		exit(EXIT_CMD);
	}
}
