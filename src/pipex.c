/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 19:55:57 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/12 14:37:57 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_files(t_pipex *pipex, int argc, char *argv[])
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		perror(ERROR_INFILE);
		printf ("errno: %d\n", errno);
		exit(errno);
	}
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		perror(ERROR_OUTFILE);
		exit(errno);
	}
}

void	status_check(int *status)
{
	if (WIFEXITED(status)) 
	{
		int exit_status = WEXITSTATUS(status);
		printf("Child 1 exited with status: %d\n", exit_status);
	}
	else if (WIFSIGNALED(status))
	{
		int term_signal = WTERMSIG(status);
		printf("Child 1 terminated by signal: %d\n", term_signal);
	}
	else if (WIFSTOPPED(status))
	{
		int stop_signal = WSTOPSIG(status);
		printf("Child 1 stopped by signal: %d\n", stop_signal);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	pid_t	pid_1;
	pid_t	pid_2;
	int		status_1;
	int		status_2;

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
	close(pipex.fds[0]);
	close(pipex.fds[1]);
	waitpid(pipex.pid1, &status_1, WUNTRACED);
	status_check(&status_1);
	waitpid(pipex.pid2, &status_2, WUNTRACED);
	status_check(&status_2);
	free_parent(&pipex);
	return (0);
}
