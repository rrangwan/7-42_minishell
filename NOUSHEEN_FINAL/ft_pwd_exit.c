/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:21:38 by nali              #+#    #+#             */
/*   Updated: 2022/06/18 09:37:15 by nali             ###   ########.fr       */
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
		exit(g_err);
	}
	else
	{
		g_err = 1;
		exit(g_err);
	}
}

//will need to update main since exit can have arguments
void	ft_exit(char **cmd)
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
		flag = 2;
		printf("exit: too many arguments\n");
	}
	else if (cmd[1] && cmd[1][0])
	{
		flag = ft_exitb(cmd);
		if (flag != 2 && cmd[1][0] == '-')
			g_err += ft_atoi(cmd[1]);
		if (flag != 2 && cmd[1][0] != '-')
			g_err = ft_atoi(cmd[1]);
	}
	if (flag != 2)
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
			printf("exit: numeric argument required\n");
			return (1);
		}
		i++;
	}
	return (0);
}
