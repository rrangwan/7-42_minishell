/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:08:56 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/17 07:10:13 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export3(char *cmd, t_var *vars)
{
	char	*name;
	char	*value;
	char	*new;

	name = ft_export5(cmd);
	value = ft_export6(cmd);
	new = ft_strjoin(name, ft_strjoin("=", value));
	free (value);
	ft_export4(name, new, vars);
}

void	ft_export4b(t_var *vars, char *new)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	while (vars->env_var[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * (i + 2));
	j = 0;
	while (j < i)
	{
		temp[j] = ft_strdup(vars->env_var[j]);
		j++;
	}
	temp[j] = ft_strdup(new);
	temp[j + 1] = NULL;
	ft_free_env(vars);
	vars->env_var = temp;
}

void	ft_export4(char *name, char *new, t_var *vars)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	while (vars->env_var[i] != NULL)
	{
		if (ft_strncmp(vars->env_var[i], name, ft_strlen(name)) == 0)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag)
			vars->env_var[i] = ft_strdup(new);
	else
		ft_export4b(vars, new);
	free(name);
	free(new);
}

char	*ft_is_export2(char **cmd)
{
	int	i;

	i = 1;
	while (i < ft_array_len(cmd))
	{
		if (ft_export7(cmd[i]) == 0)
			i++;
		if ((i < ft_array_len(cmd)) && !ft_isalpha(cmd[i][0]))
			return (ft_export5(cmd[i]));
		i++;
	}
	return (NULL);
}
