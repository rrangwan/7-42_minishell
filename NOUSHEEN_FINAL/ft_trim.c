/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 06:26:35 by nali              #+#    #+#             */
/*   Updated: 2022/06/14 09:22:31 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- COUNT QUOTES IN A TOKEN -------------*/
/*	same logic as earlier
	only count external quotes and not quotes within quotes.
	example: "hello 'tom'" 
			here we will count only the external double quotes (count = 2)
	example: "hello"'tom' 
			here we will count all quotes (count = 4)*/
int	ft_count_quotes(char *input)
{
	int		i;
	int		quote_value;
	int		open_quote;
	int		count;

	i = -1;
	quote_value = 0;
	open_quote = 0;
	count = 0;
	while (input[++i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && open_quote == 0)
			quote_value = input[i];
		if (input[i] == quote_value)
		{
			open_quote += 1;
			count += 1;
		}
		if (open_quote % 2 == 0 && open_quote > 0)
		{
			quote_value = 0;
			open_quote = 0;
		}			
	}
	return (count);
}

/*------------- COPY TOKENS TO NEW LOCATION WITHOUT QUOTES -------------*/
char	*ft_trim_quotes(char *new_str, char *str)
{
	int	quote_value;
	int	open_quote;
	int	i;
	int	k;

	quote_value = 0;
	open_quote = 0;
	i = -1;
	k = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && open_quote == 0)
			quote_value = str[i];
		if (str[i] == quote_value)
			open_quote += 1;
		if (str[i] != quote_value)
			new_str[k++] = str[i];
		if (open_quote % 2 == 0 && open_quote > 0)
		{
			quote_value = 0;
			open_quote = 0;
		}
	}
	new_str[k] = '\0';
	return (new_str);
}

/*------------- TRIMS THE TOKENS OF ANY QUOTES -------------*/
/* 	This is because, though shell syntax has 
	quotes, it cannot process quotes.*/
/*	c - number of quotes in a token
	if c > 0 (i.e., if quotes present, then reallocate memory
	new memory  = old memory - number of quotes */
char	**ft_trim(char **tokens)
{
	char	*new_str;
	int		i;
	int		c;

	i = -1;
	while (tokens[++i])
	{
		c = ft_count_quotes(tokens[i]);
		if (c > 0)
		{
			new_str = (char *)malloc(ft_strlen(tokens[i]) - c + 1);
			if (!new_str)
			{
				printf("minishell: Insufficient Memory\n");
				g_err = 1;
				return (NULL);
			}
			new_str = ft_trim_quotes(new_str, tokens[i]);
			free(tokens[i]);
			tokens[i] = new_str;
		}
	}
	return (tokens);
}
