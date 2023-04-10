/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:24 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/10 17:31:34 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void	leak_check()
// {
// 	system("leaks -q pipex");
// }

void	get_files(t_pipex *pipex, int argc, char *argv[])
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		error_msg(ERROR_INFILE);
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile ==  -1)
		error_msg(ERROR_OUTFILE);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	// atexit(leak_check);
	if (argc != 5)
		return (write(2, "Invalid argument", 16));
	get_files(&pipex, argc, argv);
	if (pipe(pipex.fds) < 0)
		error_msg(ERROR_PIPE);
	pipex.cmd_dirs = get_cmd_dirs(envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child_1(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child_2(pipex, argv, envp);
	close(pipex.fds[0]);
	close(pipex.fds[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_parent(&pipex);
	return (0);
}
