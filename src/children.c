/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:06 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/18 21:52:00 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	redirect(int in, int out)
{
	if (dup2(in, 0) == -1)
	{
		perror("failed dup2 for input");
		exit(errno);
	}
	if (dup2(out, 1) == -1)
	{
		perror("failed dup2 for output");
		exit(errno);
	}
}

void	child_1(t_pipex pipex, char *argv[], char *envp[])
{
	char	**args;
	char	**new_args;
	int		new_args_size;

	args = ft_split(argv[2], ' ');
	new_args_size = new_array_size(argv[2]);
	new_args = calloc(sizeof(char *), (new_args_size + 1));
	if (!new_args)
	{
		free_args(args);
		return ;
	}
	multiple_args(args, new_args, new_args_size);
	pipex.cmd_args = new_args;
	pipex.command = command_check(pipex.cmd_dirs, pipex.cmd_args[0]);
	if (pipex.cmd_dirs == NULL && access(pipex.cmd_args[0], X_OK) == 0)
		pipex.command = pipex.cmd_args[0];
	if (pipex.command == NULL)
	{
		cmd_error(pipex.cmd_args[0]);
		free_child(&pipex);
		exit(EXIT_CMD);
	}
	redirect(pipex.infile, pipex.fds[1]);
	close(pipex.fds[0]);
	if (execve(pipex.command, pipex.cmd_args, envp) == -1)
	{
		perror("execve error");
		exit(1);
	}
}

void	child_2(t_pipex pipex, char *argv[], char *envp[])
{
	char	**args;
	char	**new_args;
	int		new_args_size;

	args = ft_split(argv[3], ' ');
	new_args_size = new_array_size(argv[3]);
	new_args = calloc(sizeof(char *), (new_args_size + 1));
	if (!new_args)
	{
		free_args(args);
		return ;
	}
	multiple_args(args, new_args, new_args_size);
	pipex.cmd_args = new_args;
	pipex.command = command_check(pipex.cmd_dirs, pipex.cmd_args[0]);
	if (pipex.cmd_dirs == NULL && access(pipex.cmd_args[0], X_OK) == 0)
		pipex.command = pipex.cmd_args[0];
	if (pipex.command == NULL)
	{
		cmd_error(pipex.cmd_args[0]);
		free_child(&pipex);
		exit(EXIT_CMD);
	}
	redirect(pipex.fds[0], pipex.outfile);
	close(pipex.fds[1]);
	if (execve(pipex.command, pipex.cmd_args, envp) == -1)
	{
		perror("execve error");
		exit(1);
	}
}
