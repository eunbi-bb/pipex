/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:06 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/11 19:58:20 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	redirect(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	child_1(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.command = command_check(pipex.cmd_dirs, pipex.cmd_args[0]);
	if (pipex.command == NULL)
	{
		free_child(&pipex);
		error_msg(ERROR_CMD);
	}
	redirect(pipex.infile, pipex.fds[1]);
	close(pipex.fds[0]);
	execve(pipex.command, pipex.cmd_args, envp);
}

void	child_2(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.command = command_check(pipex.cmd_dirs, pipex.cmd_args[0]);
	if (pipex.command == NULL)
	{
		free_child(&pipex);
		error_msg(ERROR_CMD);
	}
	redirect(pipex.fds[0], pipex.outfile);
	close(pipex.fds[1]);
	execve(pipex.command, pipex.cmd_args, envp);
}
