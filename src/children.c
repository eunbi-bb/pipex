/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:06 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/18 02:07:52 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	array_size(char **args)
{
	int	arg_num;

	if (args == NULL)
		return (0);
	arg_num = 0;
	while (args[arg_num])
		arg_num++;
	return (arg_num);
}

void	free_newargs(char **new_args)
{
	int	i;

	i = 0;
	while (new_args[i])
	{
		free(new_args[i]);
		new_args[i] = NULL;
		i++;
	}
	free(new_args);
}

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

	args = ft_split(argv[2], ' ');
	new_args = malloc(sizeof(char *) * (array_size(args) + 1));
	if (!new_args)
	{
		free_args(args);
		return ;
	}
	multiple_args(args, new_args);
	pipex.cmd_args = new_args;
	free_args(args);
	pipex.command = command_check(pipex.cmd_dirs, pipex.cmd_args[0]);
	if (pipex.command == NULL)
	{
		error_msg(pipex.cmd_args[0]);
		free_child(&pipex);
		exit(errno);
	}
	redirect(pipex.infile, pipex.fds[1]);
	close(pipex.fds[0]);
	free_args(new_args);
	execve(pipex.command, pipex.cmd_args, envp);
}

void	child_2(t_pipex pipex, char *argv[], char *envp[])
{
	char	**args;
	char	**new_args;

	args = ft_split(argv[3], ' ');
	new_args = malloc(sizeof(char *) * (array_size(args) + 1));
	if (!new_args)
	{
		// free_args(args);
		return ;
	}
	multiple_args(args, new_args);
	pipex.cmd_args = new_args;
	// free_args(args);
	pipex.command = command_check(pipex.cmd_dirs, pipex.cmd_args[0]);
	if (pipex.command == NULL)
	{
		error_msg(pipex.cmd_args[0]);
		free_child(&pipex);
		exit(errno);
	}
	redirect(pipex.fds[0], pipex.outfile);
	close(pipex.fds[1]);
	execve(pipex.command, pipex.cmd_args, envp);
}
