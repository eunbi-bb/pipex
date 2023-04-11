/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 19:55:57 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/11 20:18:38 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_files(t_pipex *pipex, int argc, char *argv[])
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		error_msg(ERROR_INFILE);
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		error_msg(ERROR_OUTFILE);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	pid_t	pid_1;
	pid_t	pid_2;

	if (argc != 5)
		return (write(STDERR_FILENO, "Invalid argument", 16));
	get_files(&pipex, argc, argv);
	if (pipe(pipex.fds) == -1)
		error_msg(ERROR_PIPE);
	pipex.cmd_dirs = get_cmd_dirs(envp);
	pid_1 = fork();
	if (pid_1 == 0)
		child_1(pipex, argv, envp);
	pid_2 = fork();
	if (pid_2 == 0)
		child_2(pipex, argv, envp);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_parent(&pipex);
	return (0);
}
