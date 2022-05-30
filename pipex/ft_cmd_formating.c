/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_formating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 20:11:16 by nali              #+#    #+#             */
/*   Updated: 2022/02/08 23:13:04 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_command_for_quotes(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == 39)
			return (1);
		if (command[i] == 34)
			return (2);
		i++;
	}
	return (0);
}

int	ft_find_trailings_begin(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			break ;
		else
			i++;
	}
	return (i);
}

int	ft_find_trailings_end(char *cmd, int end)
{
	while (end >= 0)
	{
		if (cmd[end] != ' ')
			break ;
		else
			end--;
	}
	return (end);
}

char	**ft_strip_leading_trailing_space(char **cmd_list)
{
	int		i;
	int		front;
	int		end;
	char	*tmp;

	i = 0;
	while (cmd_list[i])
	{
		end = ft_strlen(cmd_list[i]) - 1;
		front = ft_find_trailings_begin(cmd_list[i]);
		end = ft_find_trailings_end(cmd_list[i], end);
		tmp = cmd_list[i];
		cmd_list[i] = (char *)malloc((end - front + 2) * sizeof(char));
		ft_strlcpy(cmd_list[i], &tmp[front], (end - front + 2));
		free(tmp);
		i++;
	}
	return (cmd_list);
}

char	**ft_get_command_list(char *command)
{
	int		i;
	char	**cmd_list;
	
	// in some tester we are given commands wth single and double quotes
	// when we type the command in terminal we need these quotes eg. in awk print commands
	//eg:  "awk '{count++} END {print count}'").  OR     "awk '\"{count++} END {print count}\"'"
	// but when we pass these quotes to execve command the system cannot process. so we split based space or quotes
	cmd_list = NULL;
	i = ft_check_command_for_quotes(command);
	if (i == 0)
		cmd_list = ft_split(command, ' ');
	else if (i == 1)
	{
		cmd_list = ft_split(command, 39); //single quotes
	}
	else if (i == 2)
	{
		cmd_list = ft_split(command, 34); // double quotes
	}
	return (cmd_list);
}
