/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/27 09:54:36 by eucho         #+#    #+#                 */
/*   Updated: 2023/04/12 12:30:50 by eucho         ########   odam.nl         */
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

# define COMMAND_NOT_FOUND 126
# define COMMAND_NOT_EXECUTABLE 127

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fds[2];
	int		infile;
	int		outfile;
	char	**cmd_dirs;
	char	**cmd_args;
	char	*command;
}t_pipex;

/*pipex.c*/
void	get_files(t_pipex *pipex, int argc, char *argv[]);
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