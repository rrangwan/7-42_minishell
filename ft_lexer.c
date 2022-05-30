/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 04:55:03 by nali              #+#    #+#             */
/*   Updated: 2022/05/30 07:36:51 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*splits incoming string into tokens either based on spaces or
(single/double) quotes*/

int	ft_count_tokens(char *input, int words, int i)
{
	int	quote;
	int	flg;

	quote = 0;
	flg = 0;
	while (input[i])
	{
		if (!ft_chk_spce_tab(input[i]))
		{
			words++;
			while ((!ft_chk_spce_tab(input[i]) || flg == 1) && input[i] != '\0')
			{
				if ((input[i] == '\'' || input[i] == '\"') && quote == 0)
					quote = input[i];
				flg = (flg + (input[i] == quote)) % 2;
				quote = quote * flg;
				i++;
			}
			if (flg)
				return (-1);
		}
		else
			i++;
	}
	return (words);
}

void	ft_quote_check(char *input, int *i, int *quote, int *flg)
{
	int	j;

	j = *i;
	if ((input[j] == '\'' || input[j] == '\"') && *quote == 0)
		*quote = input[j];
	*flg = (*flg + (input[j] == *quote)) % 2;
	*quote = (*quote) * (*flg);
	j++;
	*i = j;
}

char	**ft_separate_tokens(char **tokens, char *input, int i, int j)
{
	int	quote;
	int	flg;
	int	start;
	int	len;

	quote = 0;
	flg = 0;
	while (input[i])
	{
		if (!ft_chk_spce_tab(input[i]))
		{
			start = i;
			len = 0;
			while ((!ft_chk_spce_tab(input[i]) || flg == 1) && input[i] != '\0')
			{
				ft_quote_check(input, &i, &quote, &flg);
				len++;
			}
			tokens[j++] = ft_substr(input, start, len);
		}
		else
			i++;
	}
	tokens[j] = NULL;
	return (tokens);
}

char	**ft_get_tokens(char *input, int words)
{	
	int		index;
	int		j;
	char	**tokens;

	index = 0;
	j = 0;
	tokens = (char **)malloc((words + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	index = 0;
	tokens = ft_separate_tokens(tokens, input, index, j);
	if (*tokens == NULL)
	{
		ft_free_memory(tokens);
		return (NULL);
	}
	return (tokens);
}

void	ft_lexer(char *input, t_var	vars)
{
	char	**tokens;
	char	**new_tokens;
	int		i;
	int		words;

	if (!input)
		return ;
	words = 0;
	i = 0;
	words = ft_count_tokens(input, words, i);
	printf("number of words = %d\n", words);
	if (words == -1)
		return ;
	tokens = ft_get_tokens(input, words);
	if (tokens == NULL)
		return ;
	ft_expander(tokens, vars, i);
	new_tokens = ft_split_redirection_pipe(tokens, i, words);
	if (new_tokens == NULL)
	{
		ft_free_memory(tokens);
		return ;
	}
	new_tokens = ft_trim(new_tokens, i, 0, 0);
	ft_free_memory(new_tokens);
}
