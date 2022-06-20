/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:23:03 by nali              #+#    #+#             */
/*   Updated: 2022/06/20 11:29:28 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- FREE CHILD PROCESS MEMORY -------------*/
void	ft_free_child_memory(t_var *vars)
{
	ft_close_pipes(vars->pipe_fds, vars->pipe_count);
	ft_close_fds(vars->cmd_lst);
	ft_free_pipes(vars->pipe_fds, vars->pipe_count);
	ft_free_env(vars);
}

/*------------- GET COMMAND -------------*/
t_cmd	*ft_get_command_node(int index, t_var *vars)
{
	t_cmd	*tmp;
	int		j;

	j = 0;
	tmp = vars->cmd_lst;
	while (j != index)
	{
		tmp = tmp->next;
		j++;
	}
	return (tmp);
}

/*------------- EXECUTE COMMAND -------------*/
void	ft_execute(int i, t_cmd *cmd_node, t_var *vars)
{
	if (ft_set_cmd_path(cmd_node, vars) == 1)
	{
		ft_free_child_memory(vars);
		exit(127);
	}
	if (ft_dup(i, cmd_node, vars->pipe_fds) == 1)
	{
		printf("minishell: dup2 failed\n");
		ft_free_child_memory(vars);
		g_err = 1;
		exit(1);
	}
	ft_close_pipes(vars->pipe_fds, vars->pipe_count);
	ft_close_fds(vars->cmd_lst);
	g_err = 0;
	execve(cmd_node->cmd_path, cmd_node->cmd, vars->env_var);
	ft_free_pipes(vars->pipe_fds, vars->pipe_count);
	ft_free_list(vars);
	g_err = 126;
	exit(126);
}

/*------------- CHECK REDIRECTION, SET PATH, DUP & EXECUTE -------------*/
/*	Each time a child process is creted, it will get a copy of all the
	variables of the parent process. 
	If the command is executed successfully, the program will free all 
	memory. But if there is am error we have to free memory for parent
	and child separately*/
void	ft_child_process(int i, t_var *vars)
{
	t_cmd	*cmd_node;

	cmd_node = ft_get_command_node(i, vars);
	cmd_node = ft_redirections(cmd_node);
	if (cmd_node == NULL)
	{
		ft_free_child_memory(vars);
		g_err = 1;
		exit(1);
	}
	signal(SIGINT, SIG_DFL);
	if (built_in1(cmd_node->cmd, vars))
		built_in2(cmd_node->cmd, vars);
	else
		ft_execute(i, cmd_node, vars);
}
