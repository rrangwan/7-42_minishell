/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:19:17 by nali              #+#    #+#             */
/*   Updated: 2022/06/20 12:09:59 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo2(char **cmd)
{
	int		j;
	int		fd;
	int		flag;

	j = 1;
	flag = 0;
	fd = 1;
	if (cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] == '\0')
	{
		flag = 1;
		j++;
	}
	while (cmd[j])
	{
		ft_putstr_fd(cmd[j], fd);
		j++;
		if (cmd[j])
			ft_putchar_fd(' ', fd);
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
	g_err = 0;
	exit(g_err);
}

void	ft_echo(char **cmd)
{
	if (!cmd[1])
	{
		g_err = 0;
		exit(g_err);
	}
	ft_echo2(cmd);
}

void	ft_env(t_var *vars, char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		g_err = 127;
		exit(g_err);
	}
	while (vars->env_var[i])
	{
		if (ft_strchr(vars->env_var[i], '='))
			printf("%s\n", vars->env_var[i]);
		i++;
	}
	g_err = 0;
	exit(g_err);
}
