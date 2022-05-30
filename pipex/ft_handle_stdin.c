/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_stdin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:39:57 by nali              #+#    #+#             */
/*   Updated: 2022/02/08 23:17:13 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_trim_newline(char *line, char *limiter)
{
	char	*trimmed;
	int		l;
	char	newline[2];

	newline[0] = '\n';
	newline[1] = '\0';
	if (line == NULL)
		return (NULL);
	l = ft_strlen(line);
	// if limiter is not newline
	if (ft_strcmp(newline, limiter) == 0 || ft_strchr(line, '\n') == NULL)
	{
		trimmed = (char *)malloc((l + 1) * sizeof(char));
		ft_strlcpy(trimmed, line, l + 1);
	}
	else
	{
		trimmed = (char *)malloc(l * sizeof(char));
		ft_strlcpy(trimmed, line, l);
	}
	return (trimmed);
}

void	ft_read_to_file_from_stdin(t_input info)
{
	int		len;
	char	*line;
	char	*trim_line;
	char	*limiter;

	limiter = info.argv[2];
	line = get_next_line(0);
	//get next line program read including the newline. so we need to remove the newline
	trim_line = ft_trim_newline(line, limiter);
	//keep  reading till it reaches a line that contains only the limiter or EOF
	while (ft_strcmp(trim_line, limiter) != 0 && line != NULL)
	{
		len = ft_strlen(line);
		//after reading keep writing to a tmp file
		// after this the program is the same
		write(info.file1, line, len);
		if (ft_strchr(line, '\n') == NULL)
			break ;
		ft_free_mem_stdin(line, trim_line);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		trim_line = ft_trim_newline(line, limiter);
	}
	if (line != NULL && trim_line != NULL)
		ft_free_mem_stdin(line, trim_line);
}

int	ft_pipex_stdin(t_input info)
{
	int	id[2];

	id[0] = fork();
	if (id[0] == -1)
		return (1);
	if (id[0] == 0)
	{
		ft_child_process_frst_b(info.fds[0], info.file1, info.argv[3], info);
		return (1);
	}
	id[1] = fork();
	if (id[1] == -1)
		return (1);
	if (id[1] == 0)
	{
		ft_child_process_last_b(info.fds[0], info.file2, info.argv[4], info);
		return (1);
	}
	ft_free_mem_close_fd(info, info.argc - 1);
	waitpid(id[0], &info.status1, 0);
	waitpid(id[1], &info.status2, 0);
	if (info.status1 > 0 || info.status2 > 0)
		return (1);
	ft_close_fds(info.file1, info.file2);
	return (0);
}

int	ft_handle_stdin_function(int argc, char **argv, char **envp)
{
	t_input	info;

	if (argc != 6)
		return (1);
	//file2 will be appended with new input(not overwritten)
	info.file1 = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	info.file2 = open(argv[5], O_CREAT | O_WRONLY | O_APPEND, 0644);
	info.argc = argc;
	info.argv = argv;
	info.envp = envp;
	if (info.file1 < 0 || info.file2 < 0)
		return (1);
	//in case of stdin only one pipe is needed
	info.fds = ft_open_pipes_b(info.argc - 1);
	if (info.fds == NULL)
		return (1);
	ft_read_to_file_from_stdin(info);
	close(info.file1);
	info.file1 = open("tmp_file", O_RDONLY);
	if (ft_pipex_stdin(info) == 1)
		return (1);
	return (0);
}
