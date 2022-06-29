/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:18:17 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/26 17:03:01 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export8(char *cmd)
{
	int	i;

	i = 1;
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '$')
			return (1);
		i++;
	}
	return (0);
}

//checks if = present
//checks for syntax of assignement
//may not need this now, not sure
/*
int	ft_is_export(char **cmd)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (cmd[i] && cmd[i] != NULL)
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

//checks if cmd starts with =
//may not need this now, not sure
int	ft_is_export3(char *cmd)
{
	char	*ret;

	if (cmd[0] == '=')
	{
		ret = ft_export6(cmd);
		ft_putstr_fd("export: '=", 2);
		ft_putstr_fd(ret, 2);
		ft_putstr_fd("' not a valid identifier\n", 2);
		g_err = 1;
		free(ret);
		return (1);
	}
	return (0);
}
*/