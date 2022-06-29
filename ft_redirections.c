/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:25:49 by nali              #+#    #+#             */
/*   Updated: 2022/06/28 06:16:08 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- TYPES OF INPUT REDIRECTION -------------*/
/*	Evrytime a new < is encountered we need to close the previously
	opened in_fd(if it is not STDIN*/
char	**ft_input(char **str, int index, t_cmd *lst_node)
{
	if (!lst_node->cmd[index + 1])
	{
		ft_putstr_fd("minishell: parse error\n", 2);
		g_err = 258;
		return (NULL);
	}
	if (lst_node->in_fd != STDIN_FILENO)
		close(lst_node->in_fd);
	str = ft_input_redirection(str, index, &lst_node->in_fd);
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
		if (ft_strcmp(cmd[i], "<") == 1)
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
t_cmd	*ft_redirections(t_cmd *cmd_node)
{
	char	**str;

	str = cmd_node->cmd;
	cmd_node = ft_check_redirections(str, cmd_node);
	return (cmd_node);
}
