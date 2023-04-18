/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:17 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/18 17:57:04 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_msg(char	*str)
{
	perror(str);
}

void cmd_error(char *cmd)
{
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, ERROR_CMD"\n", ft_strlen(ERROR_CMD) + 1);
	exit(1);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_dirs[i])
	{
		free(pipex->cmd_dirs[i]);
		i++;
	}
	free(pipex->cmd_dirs);
	close(pipex->infile);
	close(pipex->outfile);
}

void	free_child(t_pipex *pipex)
{
	int	i;

	free(pipex->command);
	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
}
