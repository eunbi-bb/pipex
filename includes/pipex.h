/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:36 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/16 21:29:37 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> /*write, read*/
# include <stdlib.h> /*malloc, free, exit*/
# include <fcntl.h> /*open*/
# include <sys/types.h> /*pid_t*/
# include <sys/wait.h> /*waitpid*/
# include <stdio.h> /*perror*/
# include <errno.h>
# include "../libft/libft.h"

# define ERROR_INPUT "Invaild Argument"
# define ERROR_INFILE "infile"
# define ERROR_OUTFILE "outfile"
# define ERROR_PIPE "Pipe Error"
# define ERROR_CMD "Command not found"

typedef struct s_pipex
{
	pid_t	pid_1;
	pid_t	pid_2;
	int		fds[2];
	int		infile;
	int		outfile;
	char	**cmd_dirs;
	char	**cmd_args;
	char	*command;
}t_pipex;

/*pipex.c*/
void	get_files(t_pipex *pipex, int argc, char *argv[]);
/*multi_arguments.c*/
void	multiple_args(t_pipex *pipex, char *argv);
/*free_error.c*/
void	error_msg(char	*msg);
int		msg(char *msg);
void	free_parent(t_pipex *pipex);
void	free_child(t_pipex *pipex);
/*command.c*/
char	**get_cmd_dirs(char **envp);
char	*command_check(char **path, char *cmd);
/*children.c*/
void	child_1(t_pipex pipex, char *argv[], char *envp[]);
void	child_2(t_pipex pipex, char *argv[], char *envp[]);
#endif