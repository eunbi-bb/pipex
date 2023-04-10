/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:06 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/10 17:09:02 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_1(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = command_check(pipex.cmd_dirs, pipex.cmd_args[0]);
	if (pipex.cmd == NULL)
	{
		free_child(&pipex);
		error_msg(ERROR_CMD);
	}
	dup2(pipex.fds[1], 1);
	close(pipex.fds[0]);
	dup2(pipex.infile, 0);
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	child_2(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = command_check(pipex.cmd_dirs, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_child(&pipex);
		error_msg(ERROR_CMD);
	}
	dup2(pipex.fds[0], 0);
	close(pipex.fds[1]);
	dup2(pipex.outfile, 1);
	execve(pipex.cmd, pipex.cmd_args, envp);
}
