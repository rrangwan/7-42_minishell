/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:29:14 by nali              #+#    #+#             */
/*   Updated: 2022/06/17 16:32:51 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup_out(int i, t_cmd	*cmd_node, int	**pipe_fds)
{
	if (cmd_node->next != NULL)
	{
		if (dup2(pipe_fds[i][1], STDOUT_FILENO) < 0)
			return (1);
		if (cmd_node->out_fd != STDOUT_FILENO)
		{
			if (dup2(cmd_node->out_fd, pipe_fds[i][1]) < 0)
				return (1);
		}
		close(pipe_fds[i][1]);
	}
	else if (cmd_node->out_fd != STDOUT_FILENO)
	{
		if (dup2(cmd_node->out_fd, STDOUT_FILENO) < 0)
			return (1);
	}
	return (0);
}

int	ft_dup_in(int i, t_cmd	*cmd_node, int	**pipe_fds)
{
	if (i != 0)
	{
		if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) < 0)
			return (1);
		if (cmd_node->in_fd != STDIN_FILENO)
		{
			if (dup2(cmd_node->in_fd, pipe_fds[i - 1][0]) < 0)
				return (1);
		}
		close(pipe_fds[i - 1][0]);
	}
	else if (cmd_node->in_fd != STDIN_FILENO)
	{
		if (dup2(cmd_node->in_fd, STDIN_FILENO) < 0)
			return (1);
	}
	return (0);
}

int	ft_dup(int i, t_cmd	*cmd_node, int	**pipe_fds)
{
	if (ft_dup_out(i, cmd_node, pipe_fds) == 1)
		return (1);
	if (ft_dup_in(i, cmd_node, pipe_fds) == 1)
		return (1);
	return (0);
}

/*------------- DUP STDIN AND STDOUT -------------*/
/* 	The output of each command in the pipeline is connected via a pipe
	to the input of the next command. That is, each command reads the 
	previous command’s output. This connection is performed before any
	redirections specified by the command.*/
/*	Priority for redirection over pipe.
	- If input redirection file present dup with file fd.
	- Else, if not the first node, duo with pipe read end.
	- If output redirection file present dup with file fd.
	- Else if a next node is present, dup with pipe*/
// int	ft_dup(int i, t_cmd	*cmd_node, int	**pipe_fds)
// {
// 	if (cmd_node->out_fd != STDOUT_FILENO)
// 	{
// 		if (dup2(cmd_node->out_fd, STDOUT_FILENO) < 0)
// 			return (1);
// 	}
// 	else if (cmd_node->next != NULL)
// 	{
// 		if (dup2(pipe_fds[i][1], STDOUT_FILENO) < 0)
// 			return (1);
// 	}
// 	if (cmd_node->in_fd != STDIN_FILENO)
// 	{
// 		if (dup2(cmd_node->in_fd, STDIN_FILENO) < 0)
// 			return (1);
// 	}
// 	else if (i != 0)
// 	{
// 		if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) < 0)
// 			return (1);
// 	}
// 	return (0);
// }
