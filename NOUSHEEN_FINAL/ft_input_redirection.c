/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:09:29 by nali              #+#    #+#             */
/*   Updated: 2022/06/16 08:34:25 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- REMOVE THE REDIRECTION OPERATOR FROM CMD ARRAY -------------*/
char	**ft_remove_redirection(char **cmd, int c, int index)
{
	int		i;
	int		j;
	char	**new_cmd;

	new_cmd = (char **)malloc((c - 1) * sizeof(char *));
	if (!new_cmd)
		exit(1);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (i == index && cmd[i + 1])
			i += 2;
		if (cmd[i])
		{
			new_cmd[j] = (char *)malloc(ft_strlen(cmd[i]) + 1);
			if (!new_cmd[j])
				exit(1);
			ft_strlcpy(new_cmd[j], cmd[i], ft_strlen(cmd[i]) + 1);
			i++;
			j++;
		}
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

/*------------- READ FROM FILE AND WRITE TO TMP_FILE -------------*/
int	ft_read_file_write_tmp(int file_fd)
{
	int		fd;
	int		len;
	char	*str;

	fd = open("tmp_file", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (0);
	str = get_next_line(file_fd);
	while (str != NULL)
	{
		len = ft_strlen(str);
		write(fd, str, len);
		free(str);
		str = get_next_line(file_fd);
	}
	close(fd);
	return (1);
}

/*------------- < OPERATOR -------------*/
/* 	Read to tmp_file from the input file*/
/*	Then remove < operator and filename from the command array*/
char	**ft_input_redirection(char **cmd, int index, int *fd)
{
	int		count;
	char	**new_cmd;
	int		file_fd;

	file_fd = open(cmd[index + 1], O_RDONLY);
	if (file_fd < 0)
	{
		printf("minishell: no such file or directory: %s\n", cmd[index + 1]);
		g_err = 1;
		return (NULL);
	}
	if (ft_read_file_write_tmp(file_fd) == 0)
		return (NULL);
	close(file_fd);
	*fd = open("tmp_file", O_RDONLY);
	if (*fd < 0)
		return (NULL);
	count = 0;
	while (cmd[count])
		count++;
	new_cmd = ft_remove_redirection(cmd, count, index);
	ft_free_array(cmd);
	return (new_cmd);
}

/*------------- READ FROM STDIN AND WRITE TO TMP_FILE -------------*/
int	ft_read_stdin(char *limiter)
{
	int		fd;
	int		len;
	char	*str;

	fd = open("tmp_file", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (0);
	str = readline("heredoc>");
	while (ft_strcmp(str, limiter) != 1 && str != NULL)
	{
		str = ft_add_newline(str);
		len = ft_strlen(str);
		write(fd, str, len);
		free(str);
		str = readline("heredoc>");
	}
	close(fd);
	free(str);
	return (1);
}

/*------------- << OPERATOR -------------*/
/*	1. 	If present store that string as limiter
	2. 	Then remove << operator and limiter from the command array*/
char	**ft_heredoc(char **cmd, int index, int *fd)
{
	int		count;
	char	**new_cmd;

	if (ft_read_stdin(cmd[index + 1]) == 0)
	{
		printf("minishell: Error reading from std input.\n");
		g_err = 1;
		return (NULL);
	}
	*fd = open("tmp_file", O_RDONLY);
	if (*fd < 0)
	{
		printf("minishell: Error reading from std input.\n");
		g_err = 1;
		return (NULL);
	}
	count = 0;
	while (cmd[count])
		count++;
	new_cmd = ft_remove_redirection(cmd, count, index);
	ft_free_array(cmd);
	return (new_cmd);
}
