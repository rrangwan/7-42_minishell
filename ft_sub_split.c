/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 06:57:02 by nali              #+#    #+#             */
/*   Updated: 2022/05/30 06:39:42 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_split_count(char **tokens, int i)
{
	int	count;
	int	j;

	i = -1;
	count = 0;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
		{
			if (ft_strchr(">|<", tokens[i][j]) == NULL)
				count++;
			while (ft_strchr(">|<", tokens[i][j]) == NULL && tokens[i][j])
				j++;
			if (ft_strchr(">|<", tokens[i][j]) != NULL && tokens[i][j])
			{
				while (tokens[i][j] == tokens[i][j + 1])
					j++;
				count++;
			}
			if (!tokens[i][j])
				j--;
		}
	}
	return (count);
}

char	**ft_sub_split(char **new_tokens, char **tokens, int i, int *k)
{
	int	j;

	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
		{
			k[1] = j;
			while (ft_strchr(">|<", tokens[i][j]) == NULL && tokens[i][j])
				j++;
			if ((j - k[1]) > 0)
				new_tokens[k[0]++] = ft_substr(tokens[i], k[1], j - k[1]);
			k[1] = j;
			if (ft_strchr(">|<", tokens[i][j]) != NULL && tokens[i][j])
			{
				while (tokens[i][j] == tokens[i][j + 1])
					j++;
				new_tokens[k[0]++] = ft_substr(tokens[i], k[1], j - k[1] + 1);
			}
			if (!tokens[i][j])
				j--;
		}
	}
	new_tokens[k[0]] = '\0';
	return (new_tokens);
}

char	**ft_trim(char **tokens, int i, int j, int l)
{
	char	*new_str;

	i = -1;
	while (tokens[++i])
	{
		j = 0;
		l = ft_strlen(tokens[i]);
		if (tokens[i][0] == '\'' && tokens[i][l - 1] == '\'')
		{
			new_str = ft_substr(tokens[i], 1, l - 2);
			if (!new_str)
				return (NULL);
			free(tokens[i]);
			tokens[i] = new_str;
		}
		else if (tokens[i][0] == '\"' && tokens[i][l - 1] == '\"')
		{
			new_str = ft_substr(tokens[i], 1, l - 2);
			if (!new_str)
				return (NULL);
			free(tokens[i]);
			tokens[i] = new_str;
		}
	}
	return (tokens);
}
