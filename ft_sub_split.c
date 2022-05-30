/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 06:57:02 by nali              #+#    #+#             */
/*   Updated: 2022/05/30 09:32:33 by nali             ###   ########.fr       */
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

int	ft_quote_count(char *input, int i)
{
	int		quote;
	int		flg;
	int		c;

	i = -1;
	quote = 0;
	flg = 0;
	c = 0;
	while (input[++i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && quote == 0)
			quote = input[i];
		flg = (flg + (input[i] == quote)) % 2;
		c = c + (input[i] == quote);
		quote = quote * flg;
	}
	return (c);
}

char	*ft_trim_copy(char *new_str, char *str)
{
	int	quote;
	int	flg;
	int	i;
	int	k;

	quote = 0;
	flg = 0;
	i = -1;
	k = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		flg = (flg + (str[i] == quote)) % 2;
		if (str[i] != quote)
		{
			new_str[k] = str[i];
			k++;
		}
		quote = quote * flg;
	}
	new_str[k] = '\0';
	return (new_str);
}

char	**ft_trim(char **tokens, int i, int j, int c)
{
	char	*new_str;

	i = -1;
	while (tokens[++i])
	{
		c = ft_quote_count(tokens[i], j);
		new_str = (char *)malloc(ft_strlen(tokens[i]) - c + 1);
		if (!new_str)
			return (NULL);
		new_str = ft_trim_copy(new_str, tokens[i]);
		free(tokens[i]);
		tokens[i] = new_str;
	}
	return (tokens);
}
