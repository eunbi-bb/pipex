/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:17 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/12 21:30:17 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_msg(char	*str)
{
	perror(str);
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
