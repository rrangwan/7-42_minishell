/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 03:58:55 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/20 14:31:09 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cd1(t_var *vars, char *old_pwd)
{
	char	*ret;
	char	*new_pwd;
	int		i;

	i = -1;
	while (vars->env_var[++i])
	{
		if (ft_strncmp(vars->env_var[i], "OLDPWD=", 7) == 0)
			break ;
	}
	if (vars->env_var[i] == NULL)
		new_pwd = ft_strjoin(old_pwd, "/");
	else
	{
		ret = malloc(sizeof(char) * (ft_strlen(vars->env_var[i]) + 1));
		if (!ret)
		{
			ft_malloc_error();
			return (NULL);
		}
		ft_strlcpy(ret, vars->env_var[i] + 7, ft_strlen(vars->env_var[i]));
		new_pwd = ft_strjoin(ret, "/");
		free(ret);
	}
	return (new_pwd);
}

char	*ft_cd2(char **cmd, t_var *vars, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp;

	if (cmd[1][0] == '.' && cmd[1][1] == '.' && cmd[1][2] == '\0')
		new_pwd = ft_cd1(vars, old_pwd);
	else
	{
		tmp = ft_strjoin(old_pwd, "/");
		new_pwd = ft_strjoin(tmp, cmd[1]);
		free(tmp);
	}
	return (new_pwd);
}

void	ft_cd4(t_var *vars, char *new_pwd, char *old_pwd)
{
	g_err = 0;
	ft_oldpwd(vars, old_pwd);
	ft_newpwd(vars, new_pwd);
}

void	ft_cd3(char **cmd, t_var *vars, char *dir, char *old_pwd)
{
	char	*new_pwd;

	if (!cmd[1] || cmd[1] == NULL)
		new_pwd = ft_strjoin(dir, "/");
	if (cmd[1] && cmd[1][0] && cmd[1][0] == '~')
	{
		if (cmd[1][1] == '\0')
			new_pwd = ft_strjoin(dir, "/");
		else if (cmd[1][1] == '/')
			new_pwd = ft_strjoin(dir, cmd[1] + 1);
	}
	if (cmd[1] && cmd[1][0] && cmd[1][0] == '/')
		new_pwd = cmd[1];
	if (cmd[1] && cmd[1][0] && cmd[1][0] != '/' && cmd[1][0] != '~')
		new_pwd = ft_cd2(cmd, vars, old_pwd);
	ft_cd5(new_pwd, cmd);
	ft_cd4(vars, new_pwd, old_pwd);
}

void	ft_cd(char **cmd, t_var *vars)
{
	char	*dir;
	char	old_pwd[300];

	getcwd(old_pwd, sizeof(old_pwd));
	dir = getenv("HOME");
	if (cmd[1] != NULL && cmd[2] != NULL)
	{	
		if (cmd[3] != NULL)
			printf("cd: too many arguments\n");
		else
			printf("cd: string not in pwd: %s\n", cmd[1]);
		g_err = 1;
		return ;
	}
	else
		ft_cd3(cmd, vars, dir, old_pwd);
}
