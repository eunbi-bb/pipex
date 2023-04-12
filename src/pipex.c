/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 19:55:57 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/12 16:16:34 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_files(t_pipex *pipex, int argc, char *argv[])
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		perror(ERROR_INFILE);
		exit(errno);
	}
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		perror(ERROR_OUTFILE);
		exit(errno);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		status_1;
	int		status_2;

	if (argc != 5)
		return (write(STDERR_FILENO, "Invalid argument", 16));
	get_files(&pipex, argc, argv);
	if (pipe(pipex.fds) == -1)
		error_msg(ERROR_PIPE);
	pipex.cmd_dirs = get_cmd_dirs(envp);
	pipex.pid_1 = fork();
	if (pipex.pid_1 == 0)
		child_1(pipex, argv, envp);
	else if (pipex.pid_1 == -1)
		exit(EXIT_FAILURE);
	pipex.pid_2 = fork();
	if (pipex.pid_2 == 0)
		child_2(pipex, argv, envp);
	else if (pipex.pid_2 == -1)
		exit(EXIT_FAILURE);
	close(pipex.fds[0]);
	close(pipex.fds[1]);
	waitpid(pipex.pid_1, &status_1, 0);
	waitpid(pipex.pid_2, &status_2, 0);
	// if (WIFEXITED(status_1) && WIFEXITED(status_2))
		free_parent(&pipex);
	return (0);
}
