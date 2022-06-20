/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 03:47:27 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/20 12:49:46 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if only one argument
//checks the format
//adds the variable
//checks if variable name starts with a digit
void	ft_export(char **cmd, t_var *vars)
{
	int		i;
	char	*err;

	if (!cmd[1])
		return (ft_export2(vars));
	if (ft_is_export(cmd))
	{
		g_err = 1;
		return ;
	}
	i = 1;
	while (cmd[i] && cmd[i] != NULL)
	{
		if (ft_export7(cmd[i]) && ft_isalpha(cmd[i][0]))
			ft_export3(cmd[i], vars);
		i++;
	}
	err = ft_is_export2(cmd);
	if (err != NULL)
	{
		printf("export: not a valid identifier %s\n", err);
		g_err = 1;
		free(err);
		return ;
	}
}

//returns name
char	*ft_export5(char *cmd)
{
	int		i;
	char	*ret;

	i = 0;
	while (cmd[i] != '=')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, cmd, i + 1);
	return (ret);
}

// returns str after =
char	*ft_export6(char *cmd)
{
	int		i;
	char	*ret;

	i = 0;
	while (cmd[i] != '=')
		i++;
	ret = malloc(sizeof(char) * (ft_strlen(cmd) - i));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, cmd + i + 1, ft_strlen(cmd) - i + 1);
	return (ret);
}

//checks if '=' present in str
int	ft_export7(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0' && cmd[i] != '=')
		i++;
	if (ft_strlen(cmd) == i)
		return (0);
	return (1);
}

int	ft_array_len(char **cmd)
{
	int	len;

	len = 0;
	while (cmd[len])
		len++;
	return (len);
}
