/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:03:32 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/17 04:12:23 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	pwd[300];

	if (getcwd(pwd, sizeof(pwd)))
	{
		printf("%s\n", pwd);
		g_err = 0;
	}
	else
		g_err = 1;
}

void	ft_newpwd(t_var *vars, char *new_pwd)
{
	int	i;

	i = 0;
	while (vars->env_var[i])
	{
		if (ft_strncmp(vars->env_var[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	free(vars->env_var[i]);
	vars->env_var[i] = ft_strjoin("PWD=", new_pwd);
}

void	ft_oldpwd(t_var *vars, char *old_pwd)
{
	int	i;

	i = 0;
	while (vars->env_var[i])
	{
		if (ft_strncmp(vars->env_var[i], "OLDPWD=", 7) == 0)
			break ;
		i++;
	}
	free(vars->env_var[i]);
	vars->env_var[i] = ft_strjoin("OLDPWD=", old_pwd);
}
