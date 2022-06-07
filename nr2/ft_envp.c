/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 05:44:55 by nali              #+#    #+#             */
/*   Updated: 2022/06/06 11:18:33 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 	Iterates through the vars->envp to look for the variable name.
	If found, returns string after the = sign
	else returns NULL*/

char	*ft_get_envp_val(char *name, t_var *vars, int l)
{
	char	*str;
	char	*result;
	int		i;

	i = 0;
	if (!name)
		return (name);
	while (vars->env_var[i])
	{
		str = vars->env_var[i];
		if (ft_strncmp(name, str, l) == 0 && str[l] == '=')
		{
			l++;
			result = ft_substr(str, l, ft_strlen(str) - l);
			free(name);
			return (result);
		}
		i++;
	}
	free(name);
	return (NULL);
}

/*	If environment variable contains curly brace we have to 
	check for closing braces. If not found exit the program.*/
/*	If closing braces prsent, extract variable name from within
	the braces.*/
char	*ft_substr_brace(char *first, char *str, int *p)
{
	char	*sub;
	int		start_brace;
	int		j;

	j = *p;
	start_brace = j;
	while (str[j] != '}' && str[j])
		j++;
	//if no closing brace found, exit
	if (str[j] != '}')
	{
		if (first != NULL)
			free(first);
		sub = NULL;
		printf("Syntax Error\n");
		//exit the program using signals
	}
	else
		//extract the variable name without the braces
		sub = ft_substr(str, start_brace + 1, j - start_brace - 1);
	*p = j;
	return (sub);
}

char	*ft_substr_no_brace(char *str, int *p)
{
	int		l;
	char	*result;
	int		i;

	l = 0;
	i = *p; //starting position of variable name

	/*Environment variable names consists solely of uppercase letters,
	digits, and the '_' (underscore) and do not begin with a digit. */
	/* to extract variable name starting from position i ,read till it 
	encounters a value other than those mentioned above */
	while (ft_isalnum(str[i + l]) || str[i + l] == '_') 
		l++;
	result = ft_substr(str, i, l);
	//setting i to last charcter of the variable name
	i = i + l - 1;
	*p = i;
	return (result);
}

/*	Checks for variable name after $ and substitutes it with value of the
	environment variable returns NULL if no such environment variable exists*/
/*	A variable can be of the format $VAR or ${VAR}*/
char	*ft_handle_dollar(char *str, int p, t_var *vars, int qval)
{
	char	*sub;
	char	*first;
	char	*result;	

	first = NULL;
	// p is the position of the character after $
	//if p = 0 or p = 1,there will not be any chararcters before $ 
	// example: $SHELL or ${SHELL}
	//if p > 1, chararcters before $ will be stored in first
	// example:  123${SHELL}  or "${SHELL}"
	if (p > 1)
		first = ft_substr(str, 0, p - 1);
	//check if variable has curly braces in variable name"
	if (str[p] == '{')
		sub = ft_substr_brace(first, str, &p);
	else
		sub = ft_substr_no_brace(str, &p);
	// get the environment variable value to be substitued and join with first
	result = ft_strjoin_new(first, ft_get_envp_val(sub, vars, ft_strlen(sub)));
	//if characters exist after the variable name, we have to join that also with the result
	//example: echo ${SHELL}123 --> gives output --> /bin/zsh123
	//example: echo "$SHELL"abc --> gives output --> "/bin/zsh"abc
	if (str[++p])
		result = ft_strjoin_new(result, ft_substr(str, p, ft_strlen(str) - p));
	return (result);
}
