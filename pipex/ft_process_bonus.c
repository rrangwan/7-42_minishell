/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:49:18 by nali              #+#    #+#             */
/*   Updated: 2022/02/08 23:15:45 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_child_process_frst_b(int *fd_wr, int file1, char *cmd, t_input info)
{
	char	**paths;
	char	**cmd_list;

	if (dup2(fd_wr[1], STDOUT_FILENO) < 0)
		return (1);
	if (dup2(file1, STDIN_FILENO) < 0)
		return (1);
	close(file1);
	close(info.file2);
	if (ft_strcmp(info.argv[1], "here_doc") == 0)
		ft_close_pipes_b(info.fds, info.argc - 1);
	else
		ft_close_pipes_b(info.fds, info.argc);
	paths = ft_get_path_variable(info.envp);
	cmd_list = ft_get_command_list(cmd);
	cmd_list = ft_strip_leading_trailing_space(cmd_list);
	if (paths != NULL && cmd_list != NULL)
		ft_execute_command(paths, cmd_list, info.envp);
	return (1);
}

int	ft_child_process_last_b(int *fd_r, int file2, char *cmd, t_input info)
{
	char	**paths;
	char	**cmd_list;

	if (dup2(fd_r[0], STDIN_FILENO) < 0)
		return (1);
	if (dup2(file2, STDOUT_FILENO) < 0)
		return (1);
	close(file2);
	close(info.file1);
	if (ft_strcmp(info.argv[1], "here_doc") == 0)
		ft_close_pipes_b(info.fds, info.argc - 1);
	else
		ft_close_pipes_b(info.fds, info.argc);
	paths = ft_get_path_variable(info.envp);
	cmd_list = ft_get_command_list(cmd);
	cmd_list = ft_strip_leading_trailing_space(cmd_list);
	if (paths != NULL && cmd_list != NULL)
		ft_execute_command(paths, cmd_list, info.envp);
	return (1);
}

int	ft_child_process_mid_b(int *fd_r, int *fd_wr, char *cmd, t_input info)
{
	char	**paths;
	char	**cmd_list;

	if (dup2(fd_r[0], STDIN_FILENO) < 0)
		return (1);
	if (dup2(fd_wr[1], STDOUT_FILENO) < 0)
		return (1);
	close(info.file2);
	close(info.file1);
	ft_close_pipes_b(info.fds, info.argc);
	paths = ft_get_path_variable(info.envp);
	cmd_list = ft_get_command_list(cmd);
	cmd_list = ft_strip_leading_trailing_space(cmd_list);
	if (paths != NULL && cmd_list != NULL)
		ft_execute_command(paths, cmd_list, info.envp);
	return (1);
}

void	ft_error_code(int id, int status)
{
	waitpid(id, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			exit(EXIT_SUCCESS);
		else
			exit(WEXITSTATUS(status));
	}
}
