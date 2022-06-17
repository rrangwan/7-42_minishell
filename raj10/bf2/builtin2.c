/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 03:58:55 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/17 04:38:30 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd4(t_var *vars, char *new_pwd, char *old_pwd)
{
	g_err = 0;
	ft_oldpwd(vars, old_pwd);
	ft_newpwd(vars, new_pwd);
}

void	ft_cd3(char **cmd, t_var *vars, char *dir, char *old_pwd)
{
	char	*new_pwd;

	if (cmd[1] == NULL)
		new_pwd = ft_strjoin(dir, "/");
	if (cmd[1] != NULL && cmd[1][0] == '~')
	{
		if (cmd[1][1] == '\0')
			new_pwd = ft_strjoin(dir, "/");
		else if (cmd[1][1] == '/')
			new_pwd = ft_strjoin(dir, cmd[1] + 1);
	}
	if (cmd[1] != NULL && cmd[1][0] == '/')
		new_pwd = cmd[1];
	if (cmd[1] != NULL && cmd[1][0] != '/' && cmd[1][0] != '~')
		new_pwd = ft_strjoin(ft_strjoin(old_pwd, "/"), cmd[1]);
	if (cmd[1][0] == '.' && cmd[1][1] == '.' && cmd[1][2] == '\0')
		new_pwd = ft_cd1(vars);
	if (chdir(new_pwd) != 0)
	{
		printf("cd: No such file or directory: %s\n", cmd[1]);
		g_err = 1;
		return ;
	}
	ft_cd4(vars, new_pwd, old_pwd);
}

char	*ft_cd1(t_var *vars)
{
	char	*ret;
	int		i;

	i = 0;
	while (vars->env_var[i])
	{
		if (ft_strncmp(vars->env_var[i], "OLDPWD=", 7) == 0)
			break ;
		i++;
	}
	ret = malloc(sizeof(char) * (ft_strlen(vars->env_var[i]) + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, vars->env_var[i] + 7, ft_strlen(vars->env_var[i]));
	return (ft_strjoin(ret, "/"));
}

void	ft_cd(char **cmd, t_var *vars)
{
	char	*dir;
	char	old_pwd[300];

	getcwd(old_pwd, sizeof(old_pwd));
	dir = getenv("HOME");
	if (cmd[1] != NULL && cmd[2] != NULL && cmd[3] != NULL)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (cmd[2] != NULL && cmd[1] != NULL)
	{
		g_err = 1;
		printf("cd: string not in pwd: %s\n", cmd[1]);
		return ;
	}
	else
		ft_cd3(cmd, vars, dir, old_pwd);
}
