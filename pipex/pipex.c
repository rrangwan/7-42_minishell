/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:04:48 by nali              #+#    #+#             */
/*   Updated: 2022/02/08 22:56:46 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_child_process_1(int *fd, int *file_desc, char *cmd1, char *envp[])
{
	char	**paths;
	char	**cmd_list;
	int		file1;
	int		file2;

	file1 = file_desc[0];
	file2 = file_desc[1];
	//dup is used to replace a certain file desc with another one.
	//here STDIN fd is replaced by file1 desc
	if (dup2(file1, STDIN_FILENO) < 0)
		return (1);
	//here STDOUT fd is replaced by write end of the pipe
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		return (1);
	//we have to close all fds that are not being used
	//here we are closing file1 and fd[1] also coz these fds have already been copied to 
	//stdin and stdout in fd table
	close(fd[1]);
	close(fd[0]);
	close(file1);
	close(file2);
	//get the path variables in a 2d array
	paths = ft_get_path_variable(envp);
	// split the command to create a list that is null gterminated
	cmd_list = ft_get_command_list(cmd1);
	//in the list of cmds trim any trainling spaces
	//(this is used in case of a specific tester where cmds include quotes and double quotes.)
	//trailing space occurs when we split using single and double quptes
	cmd_list = ft_strip_leading_trailing_space(cmd_list);
	if (paths != NULL && cmd_list != NULL)
		ft_execute_command(paths, cmd_list, envp);
	return (1);
}

int	ft_child_process_2(int *fd, int *file_desc, char *cmd2, char *envp[])
{
	char	**paths;
	char	**cmd_list;
	int		file1;
	int		file2;

	file1 = file_desc[0];
	file2 = file_desc[1];
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return (1);
	if (dup2(file2, STDOUT_FILENO) < 0)
		return (1);
	close(fd[0]);
	close(fd[1]);
	close(file1);
	close(file2);
	paths = ft_get_path_variable(envp);
	cmd_list = ft_get_command_list(cmd2);
	cmd_list = ft_strip_leading_trailing_space(cmd_list);
	if (paths != NULL && cmd_list != NULL)
		ft_execute_command(paths, cmd_list, envp);
	return (1);
}

void	ft_close_pipes(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	pipex(int *fd, int *file_desc, char **argv, char **envp)
{
	int	id[2];
	int	status;
	//creates a child process for the current program
	//with a copy of all variables n memory
	id[0] = fork();
	if (id[0] == -1)
		return (1);
	//when child is created a process id of the parent is assigned to the child i.e., 0
	//and the parent gets the child's process id
	if (id[0] == 0)
		ft_child_process_1(fd, file_desc, argv[2], envp);
	id[1] = fork();
	if (id[1] == -1)
		return (1);
	if (id[1] == 0)
		ft_child_process_2(fd, file_desc, argv[3], envp);
	ft_close_pipes(fd);
	//asking parent to wait for the child processes to finish and get their status
	waitpid(id[0], &status, 0);
	waitpid(id[1], &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			exit(EXIT_SUCCESS);
		else
			exit(WEXITSTATUS(status));
	}
	return (0);
}

int	main(int argc, char **argv, char *envp[])
{
	int	fd[2];
	int	file_desc[2];

	if (argc != 5)
		return (1);
	
	//open files. File2 should be opened such that, when the cmd is run the file should be rewritten
	file_desc[0] = open(argv[1], O_RDONLY, 0);
	file_desc[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_desc[0] < 0 || file_desc[1] < 0)
		return (1);
	//pipe() is used for connection between two processes
	// creates a pipe with fd[0] on the read end(right side)
	//and fd[1] on the write end(left side)
	if (pipe(fd) < 0)
		return (1);
	if (pipex(fd, file_desc, argv, envp) == 1)
		return (1);
	close(file_desc[0]);
	close(file_desc[1]);
	return (0);
}
