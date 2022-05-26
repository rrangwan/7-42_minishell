/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:46:41 by nali              #+#    #+#             */
/*   Updated: 2022/05/26 08:47:54 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_substr(char *sub, t_var vars, int l)
{
	char	*str;
	char	*result;
	int		i;

	i = 0;
	if (!sub)
		return (NULL);
	while (vars.env_var[i])
	{
		str = vars.env_var[i];
		if (ft_strncmp(sub, str, l) == 0 && str[l] == '=')
		{
			l++;
			result = ft_substr(str, l, ft_strlen(str) - l);
			free(sub);
			return (result);
		}
		i++;
	}
	return (NULL);
}

char	*ft_handle_dollar(char *str, int p, t_var vars)
{
	int		s_brace;
	char	*sub;
	char	*first;
	char	*result;

	s_brace = -1;
	first = NULL;
	if (p > 1)
		first = ft_substr(str, 0, p - 1);
	if (str[p] == '{')
	{
		s_brace = p;
		while (str[p] != '}' && str[p])
			p++;
		if (str[p] != '}')
			return (NULL);
		else
			sub = ft_substr(str, s_brace + 1, p - s_brace - 1);
	}
	else
		sub = ft_substr(str, p, ft_strlen(str) - p);
	result = ft_strjoin_new(first, ft_get_substr(sub, vars, ft_strlen(sub)));
	if (str[++p] && s_brace >= 0)
		result = ft_strjoin_new(result, ft_substr(str, p, ft_strlen(str) - p));
	return (result);
}

void	ft_expander(char **tokens, t_var vars)
{
	int		i;
	int		j;
	char	*str;
	char	*sub;

	i = 0;
	while (tokens[i])
	{
		j = 0;
		str = tokens[i];
		while (str[j])
		{
			if (str[j] == '$' && str[j + 1])
			{
				sub = ft_handle_dollar(str, j + 1, vars);
				free(tokens[i]);
				tokens[i] = sub;
			}
			j++;
		}
		i++;
	}
}
