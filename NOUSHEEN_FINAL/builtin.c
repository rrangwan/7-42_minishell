/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 03:47:22 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/20 12:05:15 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in2(char **cmd, t_var *vars)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		ft_cd(cmd, vars);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		ft_env(vars, cmd);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		ft_export(cmd, vars);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		ft_unset(cmd, vars);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		ft_exit(cmd);
}

int	built_in1(char **cmd, t_var *vars)
{
	char	*str;

	str = cmd[0];
	if (!cmd || !vars || !cmd[0])
		return (0);
	if (ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "cd", 3) == 0
		|| ft_strncmp(str, "pwd", 4) == 0 || ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "export", 7) == 0 || ft_strncmp(str, "unset", 6) == 0
		|| ft_strncmp(str, "exit", 5) == 0)
		return (1);
	else
		return (0);
}
