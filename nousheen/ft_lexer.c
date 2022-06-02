/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 04:55:03 by nali              #+#    #+#             */
/*   Updated: 2022/06/02 19:31:44 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*splits incoming string into tokens either based on spaces or
(single/double) quotes*/

int	ft_count_tokens(char *s)
{
	int	words;
	int	i;
	int	quote_value; // to store which quote is open 39-single, 34-double quote
	int	open_quote; // to indicate an open quote. if 0(no quote open), if 1(one quote is open)

	words = 0;
	i = 0;
	quote_value = 0;
	open_quote = 0;
	while (s[i])
	{
		// on encountering first non-space non-tab character
		if (s[i] != '\t' && s[i] != ' ' && s[i] != '\0')
		{
			words++;
			//two cases when the following loop is executed
			//1. till a tab or space is encountered
			//2. we have an open quote in which case we dont check for tab or space
			//at the same time check if we reached end of string
			while (((s[i] != '\t' && s[i] != ' ') || open_quote == 1) && s[i])
			{
				//quote_value is changed only on first encounter of a quote
				// hence the check quote_value == 0
				if ((s[i] == '\'' || s[i] == '\"') && quote_value == 0)
					quote_value = s[i];
				//each time it encounters the same quote we increment value
				if (s[i] == quote_value) 
					open_quote += 1;
				//when 2 quotes are encountered open_quote becomes 2
				//therefore change open_quote to 0 indicating quotes have been closed
				if (open_quote % 2 == 0 && open_quote != 0)
				{
					quote_value = 0;
					open_quote = 0;
				}
				i++;
			}
			if (open_quote == 1) // when the string terminates we check if any quotes are still open, indiacting error
				return (-1);
		}
		else
			i++; //skip to next character if space or tab
	}
	return (words);
}

void	ft_separate_tokens(char **t, char *s, int c)
{
	int	i;
	int	j;
	int	start;
	int	len;
	int quote_value;
	int open_quote;

	i = 0;
	j = 0;
	quote_value = 0;
	open_quote = 0;
	//same logic as ft_count_tokens but this this we count the characters and extract the substring
	// same concept of ft_split
	while (s[i])
	{
		if (s[i] != '\t' && s[i] != ' ' && s[i] != '\0')
		{
			start = i;
			len = 0;
			while (((s[i] != '\t' && s[i] != ' ') || open_quote == 1) && s[i])
			{
				if ((s[i] == '\'' || s[i] == '\"') && quote_value == 0)
					quote_value = s[i];
				if (s[i] == quote_value)
					open_quote += 1;
				if (open_quote % 2 == 0 && open_quote > 0)
				{
					quote_value = 0;
					open_quote = 0;
				}
				i++;
				len++;
			}
			t[j] = ft_substr(s, start, len);
			j++;
		}
		else
			i++;
	}
	t[j] = NULL;
}

void	ft_lexer(char *input, t_var	*vars)
{
	int		count;
	char	**tokens;

	if (!input)
		return ;
	// first count number of tokens so we can allocate memory
	count = ft_count_tokens(input);
	printf("number of words = %d\n", count);
	if (count == -1)
	{
		printf("Invalid Quotes\n");
		return ;
	}
	tokens = (char **)malloc((count + 1) * sizeof(char *));
	if (!tokens)
	{
		printf("Insufficient Memory\n");
		return ;
	}
	ft_separate_tokens(tokens, input, count);
	ft_print_tokens(tokens);
	ft_free_tokens(tokens);
}
