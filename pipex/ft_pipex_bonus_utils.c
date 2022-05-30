/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:48:10 by nali              #+#    #+#             */
/*   Updated: 2022/02/08 23:13:18 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**ft_open_pipes_b(int argc)
{
	int	j;
	int	**fd;
	int	i;
	int	p;

	p = argc - 4;
	fd = (int **)malloc((p) * sizeof(int *));
	j = 0;
	while (j < p)
	{
		fd[j] = (int *)malloc(2 * sizeof(int));
		j++;
	}
	i = 0;
	while (i < p)
	{
		if (pipe(fd[i]) < 0)
			return (NULL);
		i++;
	}
	return (fd);
}

void	ft_close_pipes_b(int **fd, int argc)
{
	int	i;
	int	p;

	p = argc - 4;
	i = 0;
	while (i < p)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	ft_free_fd_b(int **fd, int argc)
{
	int	i;
	int	p;

	p = argc - 4;
	i = 0;
	while (i < p)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}

void	ft_free_mem_stdin(char *line, char *trim_line)
{
	free(line);
	free(trim_line);
}
