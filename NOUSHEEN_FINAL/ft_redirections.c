/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:25:49 by nali              #+#    #+#             */
/*   Updated: 2022/06/15 15:00:42 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- TYPES OF INPUT REDIRECTION -------------*/
/* 	Checks if a string exists after < or <<  operator*/
/* 	Everytime it encounters a < or <<
	The program will read from the file of STDIN respectively and store in
	tmp_file. And store the tmp_file file descriptor as in_fd for the command*/
/*	Evrytime a new < or << is encountered we need to close the previously
	opened in_fd(if it is not STDIN*/
char	**ft_input(char **str, int index, t_cmd *lst_node)
{
	if (!lst_node->cmd[index + 1])
	{
		printf("minishell: parse error\n");
		g_err = 1;
		return (NULL);
	}
	if (lst_node->in_fd != STDIN_FILENO)
		close(lst_node->in_fd);
	if (ft_strcmp(str[index], "<") == 1)
		str = ft_input_redirection(str, index, &lst_node->in_fd);
	else
		str = ft_heredoc(str, index, &lst_node->in_fd);
	return (str);
}

/*------------- HANDLES REDIRECTIONS -------------*/
/*	If redirection is found
	1. 	ft_input(),ft_output return a new command string without the redirection 
		operators, file names corresponding to the redirection and limiters
	2.	i = 0, coz everytime a str is returned, we will start 
		iterating  the new char ** from index = 0 to make sure no other
		redirection operator is present.
	3. 	'continue' coz we have set i = -1 and we dont want the program to check
		the next 'if condition' for -1 index coz it will cause seg fault.*/
t_cmd	*ft_check_redirections(char **cmd, t_cmd *cmd_node)
{
	int		i;

	i = -1;
	while (cmd && cmd[++i])
	{
		if (ft_strcmp(cmd[i], "<") == 1 || ft_strcmp(cmd[i], "<<") == 1)
		{
			cmd = ft_input(cmd, i, cmd_node);
			if (cmd == NULL)
				return (NULL);
			cmd_node->cmd = cmd;
			i = -1;
			continue ;
		}
		if (ft_strcmp(cmd[i], ">") == 1 || ft_strcmp(cmd[i], ">>") == 1)
		{
			cmd = ft_output(cmd, i, cmd_node);
			if (cmd == NULL)
				return (NULL);
			cmd_node->cmd = cmd;
			i = -1;
		}
	}
	return (cmd_node);
}

/*------------- LOOK FOR REDIRECTION OPERATORS -------------*/
/*	For each linked list node, checks for any redirection operator 
	and stores their fd */
/*	This tmp_file is needed in input_redirections. This acts as a buffer
	when we have input redirections.
	Here, we are opening the tmp_file in truncate mode and closing it.
 	Becuase, after each set of commands are executed, we need to clear this file
	for the next set of commands 
	Due to Norminette restriction truncating tmp_file here.*/
t_cmd	*ft_redirections(t_cmd *cmd_node)
{
	int		fd;
	char	**str;

	str = cmd_node->cmd;
	fd = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	close(fd);
	cmd_node = ft_check_redirections(str, cmd_node);
	return (cmd_node);
}
