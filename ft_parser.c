/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:08:32 by nali              #+#    #+#             */
/*   Updated: 2022/06/29 10:58:59 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- CHECK IF LAST REDIR IS < or << -------------*/
void	ft_input_redir_order(t_cmd *node)
{
	int		i;

	i = 0;
	while (node->cmd[i])
	{
		if (ft_strcmp(node->cmd[i], "<") == 1)
			node->here_doc = 0;
		if (ft_strcmp(node->cmd[i], "<<") == 1)
			node->here_doc = 1;
		i++;
	}
}

/*------------- INITIALIZES VARIABLES IN LINKED LIST -------------*/
/*
	cmd_lst->cmd_path 	-	to check and store path of the command(done later)
	cmd_lst->in_fd		-	by default STDIN(0) but if any input redirection is
						found, then change to that fd.
	cmd_lst->out_fd 	- 	by default STDOUT(1) but if any output redirection
						is found, then change to that fd.
	cmd_lst->here_doc	-	set to 1 if last input redirection is heredoc
	cmd_lst->heredoc_fd - 	if heredoc present change this value to the here doc 
						pipe fd
*/
/* 	if heredoc present read from STDIN and store it in a pipe and save he 
	read end fd in cmd_lst->here_fd*/
int	init_list_variables(t_var *vars)
{
	t_cmd	*cmd_lst;

	cmd_lst = vars->cmd_lst;
	while (cmd_lst != NULL)
	{
		cmd_lst->cmd_path = NULL;
		cmd_lst->in_fd = STDIN_FILENO;
		cmd_lst->out_fd = STDOUT_FILENO;
		cmd_lst->here_doc = 0;
		cmd_lst->here_fd = STDIN_FILENO;
		ft_input_redir_order(cmd_lst);
		if (ft_handle_heredoc(cmd_lst, vars) == 1)
			return (1);
		if (cmd_lst->here_doc == 0 && cmd_lst->here_fd != STDIN_FILENO)
			close (cmd_lst->here_fd);
		cmd_lst = cmd_lst->next;
	}
	return (0);
}

/*------------- EXPAND VARIABLES, REMOVE NULL ENTRIES -------------*/
/*	Expand variables and check if they need to be split again.
	eg: export ll="ls -la"
	after expansion we want the ls and -la to be saved differntly
	for execve to function correctly.
	ft_remove_null_entries - is used to removed null entries oatherwise
	they show up as spaces in the final result.
	eg: "'$USER'" "" '' $USER $USERr '"$USER"' 
	Here, $USERr returns Null and that needs to be removed.
	*/
int	ft_perform_expansion(t_var *vars)
{
	t_cmd	*cmd_lst;

	cmd_lst = vars->cmd_lst;
	while (cmd_lst != NULL)
	{
		ft_expander(cmd_lst->cmd, vars);
		cmd_lst = cmd_lst->next;
	}
	cmd_lst = vars->cmd_lst;
	while (cmd_lst != NULL)
	{
		cmd_lst->cmd = ft_remove_null_entries(cmd_lst->cmd);
		cmd_lst = cmd_lst->next;
	}
	cmd_lst = vars->cmd_lst;
	while (cmd_lst != NULL)
	{
		cmd_lst->cmd = ft_split_expander(cmd_lst->cmd);
		if (cmd_lst->cmd == NULL)
			return (1);
		cmd_lst = cmd_lst->next;
	}
	return (0);
}

/*------------- INITIALIZE LIST AND EXPAND VARIABLES-------------*/
void	ft_parser(t_var *vars)
{
	if (!vars->cmd_lst)
		return ;
	if (init_list_variables(vars) == 1)
	{
		ft_free_list(vars);
		return ;
	}
	if (ft_perform_expansion(vars) == 1)
	{
		ft_free_list(vars);
		return ;
	}
	vars->cmd_count = ft_count_cmd(vars->cmd_lst);
	ft_pipex(vars);
	ft_free_list(vars);
}
