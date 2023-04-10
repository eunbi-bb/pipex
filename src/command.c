/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:17 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/10 17:27:26 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_cmd_dirs(char **envp)
{
	char	*tmp;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	tmp = *envp + 5;
	return (ft_split(tmp, ':'));
}

char	*command_check(char **path, char *cmd)
{
	char	*command;
	char	*tmp;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, F_OK) == 0)
			return (command);
		free(tmp);
		free(command);
		path++;
	}
	return (NULL);
}