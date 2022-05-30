/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:58:33 by nali              #+#    #+#             */
/*   Updated: 2022/02/08 23:13:27 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path_variable(char *envp[])
{
	char	**paths;
	char	*str;
	int		i;

	i = 0;
	if (!envp)
	{
		return (NULL);
	}
	//in envp we need only the line starting with PATH=
	while (envp[i])
	{
		str = envp[i];
		if (ft_strncmp(str, "PATH=", 5) == 0)
			break ;
		i++;
	}
	//split the paths into 2d array based on :
	paths = ft_split(str, ':');
	return (paths);
}

void	ft_free_memory(char **paths, char **cmd_list)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	i = 0;
	while (cmd_list[i])
	{
		free(cmd_list[i]);
		i++;
	}
	free(cmd_list);
}

char	*ft_path_append_slash(char *path)
{
	int		l;
	char	end[2];
	char	*tmp;

	end[0] = '/';
	end[1] = '\0';
	l = ft_strlen(path);
	if (path[l - 1] != '/')
	{
		tmp = path;
		path = ft_strjoin(path, end);
		free(tmp);
	}
	return (path);
}

char	*ft_get_path(char **paths, char **cmd_list)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (paths[i])
	{
		// the paths in envp may or maynot have a slash at the end
		//append slash if not present
		paths[i] = ft_path_append_slash(paths[i]);
		//append the command to the path
		//eg in if cmd is "ls -l" add only "ls" to the path
		cmd_path = ft_strjoin(paths[i], cmd_list[0]);
		//check if the folder for the command exists in the system
		//if yes return that cmd path
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		//ese keep iterating till you find the path
		free(cmd_path);
		i++;
	}
	//if cmd not present return null
	return (NULL);
}

void	ft_execute_command(char **paths, char **cmd_list, char *envp[])
{
	char	*cmd_path;

	cmd_path = ft_get_path(paths, cmd_list);
	if (cmd_path == NULL)
	{
		write(2, "pipex: ", 7);
		write(2, cmd_list[0], ft_strlen(cmd_list[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}	
	else
		execve(cmd_path, cmd_list, envp);
	//free will happen only id command wasn't executed
	//execve is succeful it automatically frees all memory
	free(cmd_path);
	ft_free_memory(paths, cmd_list);
}
