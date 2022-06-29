/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 07:20:43 by nali              #+#    #+#             */
/*   Updated: 2022/06/28 06:55:45 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- CREATE PROCESSES TO EXECUTE CMDS -------------*/
/* 	Each child process will execute one node of linked list*/
void	ft_fork(t_var *vars)
{
	int	i;
	int	id[2];

	i = -1;
	while (++i <= vars->pipe_count)
	{
		id[0] = fork();
		if (id[0] == -1)
			return ;
		if (id[0] == 0)
			ft_child_process(i, vars);
	}
	ft_close_pipes(vars->pipe_fds, vars->pipe_count);
	if (ft_strcmp(vars->cmd_lst->cmd[0], "./minishell") == 0)
	{
		signal(SIGINT, ft_sig_handler2);
		signal(SIGQUIT, ft_sig_handler2);
	}
	i = -1;
	while (++i <= vars->pipe_count)
	{
		wait(&id[1]);
		if (WIFEXITED(id[1]))
			g_err = WEXITSTATUS(id[1]);
	}
}

/*------------- BUILTIN IN PARENT PROCESS-------------*/
/*  if it is a single command also it is one of the builtins(exit,cd, export 
	or unset) we should not go into the child processes.
	Commands that change values in the parent process have to be executed
	in the parent. They must be executed in child processes if there are pipes.
	Creating different copies of these function(except EXIT function) 
	for child and parent. If executed in parent, control should return.
	If executed in child, the process should exit at the end of execution, so 
	that the process doesn't hang*/
int	ft_builtin_parent(t_cmd	*cmd_lst, t_var *vars)
{
	if (vars->pipe_count > 0)
		return (0);
	if (ft_strncmp(cmd_lst->cmd[0], "exit", 5) == 0)
	{
		ft_trim_pipex(cmd_lst);
		ft_exit(cmd_lst->cmd);
		return (1);
	}
	else if (ft_strncmp(cmd_lst->cmd[0], "cd", 3) == 0)
	{
		ft_goto_cd_parent(cmd_lst, vars);
		return (1);
	}
	else if (ft_strncmp(cmd_lst->cmd[0], "unset", 6) == 0)
	{
		ft_goto_unset_parent(cmd_lst, vars);
		return (1);
	}
	else if (ft_strncmp(cmd_lst->cmd[0], "export", 7) == 0)
	{
		ft_goto_export_parent(cmd_lst, vars);
		return (1);
	}
	return (0);
}

/*------------- CREATE PIPES  -------------*/
/* 	Each child node will execute one node of linked list and 
	start forking processes*/
void	ft_pipex(t_var *vars)
{
	vars->pipe_count = vars->cmd_count - 1;
	if (vars->pipe_count > 0)
		vars->pipe_fds = ft_open_pipes(vars->pipe_count);
	if (vars->pipe_count > 0 && vars->pipe_fds == NULL)
		return ;
	if (ft_builtin_parent(vars->cmd_lst, vars) == 1)
	{
		ft_close_fds(vars->cmd_lst);
		ft_free_pipes(vars->pipe_fds, vars->pipe_count);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_fork(vars);
	ft_close_fds(vars->cmd_lst);
	ft_free_pipes(vars->pipe_fds, vars->pipe_count);
}
