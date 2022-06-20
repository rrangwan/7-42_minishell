/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 05:44:55 by nali              #+#    #+#             */
/*   Updated: 2022/06/14 09:19:58 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- LOOKUP VALUE ENV VALUE -------------*/
char	*ft_envp(char *name, int l, t_var *vars)
{
	char	*str;
	char	*result;
	int		i;

	i = 0;
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
	return (NULL);
}

/*------------- FIND ENV VARIABLE NAME AND GET ITS VALUE -------------*/
/* 	Iterates through the vars->envp to look for the variable name.
	if name is ?, it returns the error code g_err
	If found, returns string after the = sign
	else returns NULL*/
/*char *getenv(const char *str) searches for environment
 pointed to by str and returns its value.*/
char	*ft_get_envp_val(char *name, t_var *vars)
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
	l = ft_strlen(name);
	result = ft_envp(name, l, vars);
	free(name);
	return (result);
}

/*------------- IF VARIABLE NAME WITHIN BRACES -------------*/
/*	If environment variable contains curly brace we have to 
	check for closing braces. If not found exit the program.*/
/*	If closing braces prsent, extract variable name from within
	the braces.
	Else, exit with syntax error*/
char	*ft_substr_brace(char *first, char *str, int *p)
{
	char	*sub;
	int		start_brace;
	int		j;

	j = *p;
	start_brace = j;
	while (str[j] != '}' && str[j])
		j++;
	if (str[j] != '}')
	{
		if (first != NULL)
			free(first);
		sub = NULL;
		printf("minishell: Syntax Error: no closing brace.\n");
	}
	else
		sub = ft_substr(str, start_brace + 1, j - start_brace - 1);
	*p = j;
	return (sub);
}

/*------------- IF VARIABLE NAME NOT WITHIN BRACES -------------*/
/*	p - starting position of variable name

	Environment variable names consists solely of uppercase letters,
	digits, and the '_' (underscore) and do not begin with a digit. 
	To extract variable name starting from starting position and read till
	it encounters a value other than those mentioned above 
	
	After geting the variable name set i to last character of the variable name
	*/
char	*ft_substr_no_brace(char *str, int *p)
{
	int		l;
	char	*result;
	int		i;

	l = 0;
	i = *p;
	if (str[i] == '?')
	{
		result = (char *)malloc(2);
		if (!result)
		{
			ft_malloc_error();
			return (NULL);
		}
		result[0] = '?';
		result[1] = '\0';
		return (result);
	}
	while (ft_isalnum(str[i + l]) || str[i + l] == '_')
		l++;
	result = ft_substr(str, i, l);
	i = i + l - 1;
	*p = i;
	return (result);
}

/*------------- EXPANDS ENV VARIABLES -------------*/
/*	Checks for variable name after $ and substitutes it with value of the
	environment variable returns NULL if no such environment variable exists*/
/*	A variable can be of the format $VAR or ${VAR}

	p is the position of the character after $
		if p = 0 or p = 1,there will not be any chararcters before $ 
		example: $SHELL or ${SHELL}
		if p > 1, chararcters before $ will be stored in first
		example:  123${SHELL}  or "${SHELL}"
		
	Check if variable has curly braces in variable name. If yes, extract the 
	variable name between the braces
	
	Get the environment variable value to be substitued and join with first
	
	If characters exist after the variable name, we have to join that also with
	the result.
	example: echo ${SHELL}123 --> gives output --> /bin/zsh123
	example: echo "$SHELL"abc --> gives output --> "/bin/zsh"abc*/
char	*ft_handle_dollar(char *str, int p, t_var *vars)
{
	char	*var_name;
	char	*sub_str;
	char	*first;
	char	*result;	

	first = NULL;
	if (p > 1)
		first = ft_substr(str, 0, p - 1);
	if (str[p] == '{')
		var_name = ft_substr_brace(first, str, &p);
	else
		var_name = ft_substr_no_brace(str, &p);
	sub_str = ft_get_envp_val(var_name, vars);
	result = ft_strjoin_new(first, sub_str);
	if (str[++p])
		result = ft_strjoin_new(result, ft_substr(str, p, ft_strlen(str) - p));
	return (result);
}
