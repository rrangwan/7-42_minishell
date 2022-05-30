/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 05:07:35 by nali              #+#    #+#             */
/*   Updated: 2022/05/30 06:38:55 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (1);
	else
		return (0);
}

int	ft_chk_spce_tab(char ch)
{
	if (ch == ' ' || ch == '\t')
		return (1);
	else
		return (0);
}

void	ft_free_memory(char **tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
	}
}

void	ft_free_env(t_var *vars)
{
	int	i;

	i = 0;
	if (vars)
	{
		while (vars->env_var[i])
		{
			free(vars->env_var[i]);
			i++;
		}
		free(vars->env_var);
	}
}

void	ft_print_tokens(char **tokens)
{
	int	i;

	printf("hi there\n");
	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}
