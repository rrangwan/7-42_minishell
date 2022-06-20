/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:08:32 by nali              #+#    #+#             */
/*   Updated: 2022/06/17 16:44:08 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- INITIALIZES VARIABLES IN LINKED LIST -------------*/
/*
	cmd_lst->cmd_path 	-	to check and store path of the command(done later)
	cmd_lst->in_fd		-	by default STDIN(0) but if any input redirection is
						found, then change to that fd.
	cmd_lst->out_fd 	- 	by default STDOUT(1) but if any output redirection
						is found, then change to that fd.*/
void	init_list_variables(t_var *vars)
{
	t_cmd	*cmd_lst;

	cmd_lst = vars->cmd_lst;
	while (cmd_lst != NULL)
	{
		cmd_lst->cmd_path = NULL;
		cmd_lst->in_fd = STDIN_FILENO;
		cmd_lst->out_fd = STDOUT_FILENO;
		cmd_lst = cmd_lst->next;
	}
}

/*------------- STORES TOKENS IN LIST FORMAT -------------*/
void	ft_parser(char **tokens, t_var *vars)
{
	ft_create_list(tokens, vars);
	ft_free_tokens(tokens);
	if (!vars->cmd_lst)
		return ;
	vars->cmd_count = ft_count_cmd(vars->cmd_lst);
	init_list_variables(vars);
	ft_pipex(vars);
	ft_free_list(vars);
}
