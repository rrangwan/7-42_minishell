/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:04:48 by nali              #+#    #+#             */
/*   Updated: 2022/02/08 23:16:49 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_goto_child_process_b(int i, int m, t_input info)
{
	char	**args;

	args = info.argv;
	if (i == 2 && m == 0)
		ft_child_process_frst_b(info.fds[m], info.file1, args[i], info);
	else if (i == info.argc - 2)
		ft_child_process_last_b(info.fds[m - 1], info.file2, args[i], info);
	else
		ft_child_process_mid_b(info.fds[m - 1], info.fds[m], args[i], info);
}

void	ft_free_mem_close_fd(t_input info, int num)
{
	ft_close_pipes_b(info.fds, num);
	ft_free_fd_b(info.fds, num);
}

void	ft_close_fds(int f1, int f2)
{
	close(f1);
	close(f2);
}

int	pipex_b(t_input	info)
{
	int		id;
	int		i;
	int		m;

	i = 2;
	m = 0;
	while (i < info.argc - 1)
	{
		id = fork();
		if (id == -1)
			return (1);
		if (id == 0)
		{
			ft_goto_child_process_b(i, m, info);
			return (1);
		}
		m++;
		i++;
	}
	ft_free_mem_close_fd(info, info.argc);
	ft_error_code(id, info.status1);
	ft_close_fds(info.file1, info.file2);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_input	info;

	if (argc < 5)
		return (1);
	// here_doc is the second variable read input from stdin rather than a file
	if (ft_strcmp(argv[1], "here_doc") == 0)
		ft_handle_stdin_function(argc, argv, envp);
	else
	{
		info.file1 = open(argv[1], O_RDONLY);
		info.file2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		info.argc = argc;
		info.argv = argv;
		info.envp = envp;
		if (info.file1 < 0)
			perror("pipex: input");
		// number of pipes depends on the number of cmds being used
		info.fds = ft_open_pipes_b(info.argc);
		if (info.fds == NULL)
			return (1);
		if (pipex_b(info) == 1)
			return (1);
	}
	return (0);
}
