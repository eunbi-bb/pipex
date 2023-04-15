/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:06 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/15 23:27:24 by eunbi         ########   odam.nl         */
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
// void	rest_args(t_pipex *pipex, char *argv)
// {
// 	char *first;
// 	char *rest;
// 	char **args;
// 	int	first_len;
// 	int	total_len;

// 	args = ft_split(argv, ' ');
// 	total_len = ft_strlen(argv);
// 	first = args[0];
// 	first_len = ft_strlen(first);
// 	rest = ft_substr(argv, (first_len + 1), total_len - first_len - 1);
// 	printf("first = %s\n", first);
// 	printf("rest = %s\n", rest);
// 	pipex->cmd_args[0] = first;
// 	printf("args[0] = %s\n", pipex->cmd_args[0]);
// 	pipex->cmd_args[1] = rest;
// 	printf("args[1] = %s\n", pipex->cmd_args[1]);
// }
#include <string.h>

void	multiple_args(t_pipex *pipex, char *argv)
{
	char	**args;
	int		i;
	char	**new_args;
	int		new_arg_index;
	int		keep_reading;
	int		arg_num;

	args = ft_split(argv, ' ');
	i = 0;
	while (args[i])
		i++;
	arg_num = i;
	new_args = malloc(sizeof(char *) * (arg_num + 1));
	if (!new_args)
		return ;
	new_arg_index = 0;
	keep_reading = 0;
	// printf("args[0] : %s\n", args[0]);
	// printf("args[1] : %s\n", args[1]);
	// printf("args[2] : %s\n", args[2]);
	// printf("args[3] : %s\n", args[3]);
	i = 0;
	while (args[i])
	{
		if (keep_reading == 1)
		{
			if (new_args[new_arg_index][ft_strlen(new_args[new_arg_index]) - 1] != '\'')
			{
				strcat(new_args[new_arg_index], args[i]);
				strcat(new_args[new_arg_index], " ");
			}
			else
				strcat(new_args[new_arg_index], args[i]);
		}
		else
		{
			new_args[new_arg_index] = malloc(ft_strlen(args[i]) + 1);
			strcpy(new_args[new_arg_index], args[i]);
		}
		if (args[i][0] == '\'')
			keep_reading = 1;
		if (args[i][ft_strlen(args[i]) - 1] == '\'')
			keep_reading = 0;
		printf("new_args[%i] : %s\n", new_arg_index, new_args[new_arg_index]);
		printf("%c\n", args[i][ft_strlen(args[i]) - 1]);
		if (keep_reading == 0)
			new_arg_index++;
		i++;
	}
	new_args[new_arg_index + 1] = '\0';
	pipex->cmd_args = new_args;
	i = 0;
    while (args[i]) {
        free(args[i]);
        i++;
    }
    free(args);
    i = 0;
    while (new_args[i]) {
        free(new_args[i]);
        i++;
    }
    free(new_args);
	// int j = 0;
	// while (args[j])
	// {
	// 	printf("args[%d] =%s\n", j, args[j]);
	// 	j++;
	// }
}

void	child_1(t_pipex pipex, char *argv[], char *envp[])
{
	multiple_args(&pipex, argv[2]);
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
	if (0)
		multiple_args(&pipex, argv[3]);
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
