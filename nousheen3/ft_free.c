/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:29:15 by nali              #+#    #+#             */
/*   Updated: 2022/06/08 06:23:56 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_var *vars)
{
	int	i;

	i = 0;
	if (vars)
	{
		while (vars->env_var[i])
		{
			free(vars->env_var[i]);
			i++;
		}
		free(vars->env_var);
	}
}

void	ft_free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
	}
}

// void	ft_free_list(t_cmd *cmd_lst)
// {
// 	t_cmd	*tmp;
// 	int		i;

// 	while (cmd_lst != NULL)
// 	{
// 		tmp = cmd_lst;
// 		cmd_lst = cmd_lst->next;
// 		if (tmp->cmd)
// 		{
// 			i = 0;
// 			while (tmp->cmd[i])
// 			{
// 				free(tmp->cmd[i]);
// 				i++;
// 			}
// 			free(tmp->cmd);
// 		}
// 		free(tmp);
// 		cmd_lst = NULL;
// 	}
// }

void	ft_free_list(t_var *vars)
{
	t_cmd	*cmd_lst;
	t_cmd	*tmp;
	int		i;

	cmd_lst = vars->cmd_lst;
	while (cmd_lst != NULL)
	{
		tmp = cmd_lst;
		cmd_lst = cmd_lst->next;
		if (tmp->cmd)
		{
			i = 0;
			while (tmp->cmd[i])
			{
				free(tmp->cmd[i]);
				i++;
			}
			free(tmp->cmd);
		}
		free(tmp);
	}
	vars->cmd_lst = NULL;
}