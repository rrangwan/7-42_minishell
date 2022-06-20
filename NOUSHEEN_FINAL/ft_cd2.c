/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:03:32 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/20 09:53:59 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(new_pwd);
}

//if cd .. is run as the first cmd, env will not have an entry
//  for old_pwd and therefore gives a segfault. Hence, check for
//for the NULL condition
void	ft_oldpwd_2(t_var *vars, char *old_pwd, int i)
{
	int		j;
	char	**temp;

	temp = (char **)malloc(sizeof(char *) * (i + 2));
	j = 0;
	while (j < i)
	{
		temp[j] = ft_strdup(vars->env_var[j]);
		j++;
	}
	temp[j] = ft_strjoin("OLDPWD=", old_pwd);
	temp[j + 1] = NULL;
	ft_free_env(vars);
	vars->env_var = temp;
}

void	ft_oldpwd(t_var *vars, char *old_pwd)
{
	int		i;

	i = 0;
	while (vars->env_var[i])
	{
		if (ft_strncmp(vars->env_var[i], "OLDPWD=", 7) == 0)
			break ;
		i++;
	}
	if (vars->env_var[i] != NULL)
	{
		free(vars->env_var[i]);
		vars->env_var[i] = ft_strjoin("OLDPWD=", old_pwd);
	}
	else
		ft_oldpwd_2(vars, old_pwd, i);
}

//checks if directory present
void	ft_cd5(char	*new_pwd, char **cmd)
{
	if (chdir(new_pwd) != 0)
	{
		printf("cd: No such file or directory: %s\n", cmd[1]);
		g_err = 1;
		return ;
	}
}
