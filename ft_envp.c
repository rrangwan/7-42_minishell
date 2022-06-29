/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:02:25 by nali              #+#    #+#             */
/*   Updated: 2022/06/24 18:51:35 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*------------- CHECK SHELL VARIABLES IN CASE OF BRACES -------------*/
/*	flag is 1 if braces are present
	echo ${1USER}		--->		error
	ECHO ${12USER}		--->		error
	ECHO ${AUSER}		--->		NULL
	ECHO ${A12USER}		--->		NULL*/
char	*ft_envp_braces(char *name, int *flag)
{
	if (name[0] && ft_isdigit(name[0]))
	{
		ft_putstr_fd("minishell: {", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("}: bad substitution\n", 2);
		*flag = -1;
		return (NULL);
	}
	return (NULL);
}

/*------------- LOOKUP VALUE ENV VALUE -------------*/
/*	if env variable cannot be found, check following conditions
	echo $1USER		--->		USER
	ECHO $12USER	--->		2USER
	ECHO $123USER	--->		23USER
	ECHO $AUSER		--->		NULL
	ECHO $A12USER	--->		NULL
*/
char	*ft_envp(char *name, int l, t_var *vars, int *flag)
{
	char	*str;
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (name[i] == '\'' || name[i] == '\"')
		result = ft_strdup(name);
	while (vars->env_var[i])
	{
		str = vars->env_var[i];
		if (ft_strncmp(name, str, l) == 0 && str[l] == '=')
		{
			l++;
			result = ft_substr(str, l, ft_strlen(str) - l);
			return (result);
		}
		i++;
	}
	if (name[0] && name[1] && ft_isdigit(name[0]) && *flag == 0)
		result = ft_substr(name, 1, ft_strlen(name));
	else if (*flag == 1)
		result = ft_envp_braces(name, flag);
	return (result);
}

/*------------- FIND ENV VARIABLE NAME AND GET ITS VALUE -------------*/
/* 	Iterates through the vars->envp to look for the variable name.
	if name is ?, it returns the error code g_err
	If found, returns string after the = sign
	else returns NULL*/
/*char *getenv(const char *str) searches for environment
 pointed to by str and returns its value.*/
char	*ft_get_envp_val(char *name, t_var *vars, int *flag)
{
	char	*result;
	int		l;

	if (!name)
		return (name);
	if (ft_strcmp(name, "?") == 1)
	{
		result = ft_itoa(g_err);
		free(name);
		return (result);
	}
	if (ft_strcmp(name, "$=") == 1 || ft_strcmp(name, "$+") == 1)
		return (name);
	if (name[0] && name[1] && name[0] == '$' && name[1] == ' ')
		return (name);
	l = ft_strlen(name);
	result = ft_envp(name, l, vars, flag);
	free(name);
	return (result);
}
