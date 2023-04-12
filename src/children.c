/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:06 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/12 18:07:20 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	redirect(int in, int out)
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

// void	grep_check(t_pipex *pipex)
// {
// 	int		len;
// 	int		i;
// 	char	**args;
// 	char	*tmp;

// 	args = pipex->cmd_args;
// 	i = 0;
// 	while (args[i])
// 		i++;
// 	printf("arg num = %d\n", i);
// 	if (i >= 3)
// 	{
// 		i = 1;
// 		len = 0;
// 		while (args[i] != NULL)
// 		{
// 			len += ft_strlen(args[i]);
// 			i++;
// 		}
// 		tmp = malloc(sizeof(char) * (len + 1));
// 		tmp[0] = '\0';
// 		i = 1;
// 		while (args[i] != NULL)
// 		{
// 			tmp = ft_strjoin(args[i], " ");
// 			ft_strlcat(tmp, args[++i], len + 2);
// 			free(args[i]);
// 			i++;
// 		}
// 		printf("tmp = %s\n", tmp);
// 		pipex->cmd_args[1] = tmp;
// 		free(tmp);
// 		i = 2;
// 		while (pipex->cmd_args[i] != NULL)
// 		{
// 			free(pipex->cmd_args[i]);
// 			i++;
// 		}
// 	}
// }
void	rest_args(t_pipex *pipex, char *argv)
{
	char *first;
	char *rest;
	char **args;
	int	first_len;
	int	total_len;

	args = ft_split(argv, ' ');
	total_len = ft_strlen(argv);
	first = args[0];
	first_len = ft_strlen(first);
	rest = ft_substr(argv, (first_len + 1), total_len - first_len - 1);
	printf("rest = %s\n", rest);
	pipex->cmd_args[0] = first;
	printf("args[0] = %s\n", pipex->cmd_args[0]);
	pipex->cmd_args[1] = rest;
	printf("args[1] = %s\n", pipex->cmd_args[1]);
}

void	child_1(t_pipex pipex, char *argv[], char *envp[])
{
	rest_args(&pipex, argv[2]);
	pipex.command = command_check(pipex.cmd_dirs, pipex.cmd_args[0]);
	if (pipex.command == NULL)
	{
		free_child(&pipex);
		error_msg(ERROR_CMD);
		exit(errno);
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
		exit(errno);
	}
	redirect(pipex.fds[0], pipex.outfile);
	close(pipex.fds[1]);
	execve(pipex.command, pipex.cmd_args, envp);
}
