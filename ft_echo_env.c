/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:19:17 by nali              #+#    #+#             */
/*   Updated: 2022/06/21 14:39:20 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo2(char **cmd)
{
	int		flag;
	int		k;
	int		i;
	int		j;

	flag = 0;
	k = 1;
	j = 1;
	i = 1;

//fixed for echo -nnn -nn nn hi
	while (cmd[k][1] == 'n')
	{
		while (cmd[k][0] == '-' && cmd[k][i] == 'n')
			i++;
		if (cmd[k][i] == '\0')
		{
			flag = 1;
			j++;
		}
		i = 1;
		k++;

	}
	while (cmd[j])
	{
		printf("%s", cmd[j]);
		j++;
		if (cmd[j])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	g_err = 0;
	exit(g_err);
}

void	ft_echo(char **cmd)
{
	if (!cmd[1])
	{
		printf("\n");
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
