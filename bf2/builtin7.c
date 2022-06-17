/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:18:17 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/17 07:18:32 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_export2b(t_var *vars)
{
	int		len;
	int		i;
	char	**array;

	len = 0;
	while (vars->env_var[len])
		len++;
	array = (char **) malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (vars->env_var[i])
	{
		array[i] = ft_strdup(vars->env_var[i]);
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	ft_export2c(char **array, t_var *vars)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	len = 0;
	while (vars->env_var[len])
		len++;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strncmp(array[j], array[j + 1], ft_strlen(array[j])) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_export2(t_var *vars)
{
	int		i;
	char	**array;

	array = ft_export2b(vars);
	ft_export2c(array, vars);
	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_is_export(char **cmd)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (cmd[i] != NULL)
	{
		if (ft_export7(cmd[i]) == 0)
			j++;
		if (cmd[i] != NULL)
			if (ft_is_export3(cmd[i]) == 1)
				return (1);
		i++;
	}
	if ((ft_array_len(cmd) - 1) == j)
		return (1);
	return (0);
}

int		ft_is_export3(char *cmd)
{
	char	*ret;

	if (cmd[0] == '=')
	{
		if (cmd[1] != '\0')
		{
			ret = ft_export6(cmd);
			printf("%s not found\n", ret);
			free(ret);
			return (1);
		}
		else if (cmd[1] == '\0')
		{
			printf("bad assignment\n");
			return (1);
		}
	}
	return (0);
}
