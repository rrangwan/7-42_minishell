/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 07:20:43 by nali              #+#    #+#             */
/*   Updated: 2022/06/19 18:22:33 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- CREATE PROCESSES TO EXECUTE CMDS -------------*/
/* 	Each child process will execute one node of linked list*/
void	ft_fork(t_var *vars)
{
	int	i;
	int	id;
	int	status;

	i = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, ft_sig_handler);
	while (i <= vars->pipe_count)
	{
		id = fork();
		if (id == -1)
			return ;
		if (id == 0)
			ft_child_process(i, vars);
		i++;
	}
	ft_close_pipes(vars->pipe_fds, vars->pipe_count);
	i = 0;
	while (i <= vars->pipe_count)
	{
		wait(&status);
		if (WIFEXITED(status))
			g_err = WEXITSTATUS(status);
		i++;
	}
}

/*------------- CHECK IF LAST COMMAND IS CD or EXIT -------------*/
/* 	If alst command is exit or cd we need not go into the child processes.
	This holds true for a single command without pipes.
	
	EXIT - we do not want to go into child process beacuse if ft_exit is
	executed there, there is no way to inform parent to exit also.
	cmd1 |cmd2| exit should also exit the parent.
	CD - if ft_cd is executed in child, OLDPWD AND NEWPWD are changed
	in the child and not reflected in parent. So if the command is simply cd 
	or cm1|cmd2|cd the parent should changed folder
	*/
int	ft_check_last_cmd(t_cmd	*cmd_lst, t_var *vars)
{
	while (cmd_lst->next)
		cmd_lst = cmd_lst->next;
	if (ft_strncmp(cmd_lst->cmd[0], "exit", 5) == 0)
	{
		ft_exit(cmd_lst->cmd);
		return (1);
	}
	else if (ft_strncmp(cmd_lst->cmd[0], "cd", 3) == 0)
	{
		ft_cd(cmd_lst->cmd, vars);
		return (1);
	}
	else if (ft_strncmp(cmd_lst->cmd[0], "unset", 6) == 0)
	{
		ft_unset(cmd_lst->cmd, vars);
		return (1);
	}
	else if (ft_strncmp(cmd_lst->cmd[0], "export", 7) == 0)
	{
		ft_export(cmd_lst->cmd, vars);
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
	vars->pipe_fds = ft_open_pipes(vars->pipe_count);
	if (vars->pipe_count > 0 && vars->pipe_fds == NULL)
		return ;
	if (ft_check_last_cmd(vars->cmd_lst, vars) == 1)
	{
		ft_close_fds(vars->cmd_lst);
		ft_free_pipes(vars->pipe_fds, vars->pipe_count);
		return ;
	}
	ft_fork(vars);
	ft_close_fds(vars->cmd_lst);
	ft_free_pipes(vars->pipe_fds, vars->pipe_count);
}
