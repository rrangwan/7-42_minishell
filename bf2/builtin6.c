/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:08:56 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/17 04:36:23 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset2(int j, t_var *vars)
{
	while (vars->env_var[j])
	{
		vars->env_var[j] = vars->env_var[j + 1];
		j++;
	}
	free(vars->env_var[j]);
	g_err = 0;
}

void	ft_unset(char **cmd, t_var *vars)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		temp = ft_strjoin(cmd[i], "=");
		while (vars->env_var[j])
		{
			if (ft_strncmp(vars->env_var[j], temp, ft_strlen(temp)) == 0)
			{
				ft_unset2(j, vars);
				break ;
			}
			j++;
		}
		free(temp);
		i++;
	}
}

//will need to update main since exit can have arguments
void	ft_exit(char **cmd, t_var *vars)
{
	int	flag;

	flag = 0;
	if (!cmd[1])
	{
		g_err = 0;
		flag = 1;
	}
	else if (cmd[2] != NULL)
	{
		g_err = 1;
		flag = 1;
		printf("exit: too many arguments\n");
	}
	else if (cmd[1] && cmd[1][0])
		flag = ft_exitb(cmd);
	if (flag == 0 && cmd[1][0] == '-')
		g_err = g_err + ft_atoi(cmd[1]);
	if (flag == 0 && cmd[1][0] != '-')
		g_err = ft_atoi(cmd[1]);
	ft_free_env(vars);
	exit(g_err);
}

int	ft_exitb(char **cmd)
{
	int	i;

	if (cmd[1][0] == '-')
		i = 1;
	else
		i = 0;
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			g_err = 2;
			printf("exit: %s: numeric argument required\n", cmd[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
