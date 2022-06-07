/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 04:55:03 by nali              #+#    #+#             */
/*   Updated: 2022/06/07 20:10:12 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*splits incoming string into tokens either based on spaces or
(single/double) quotes*/

/* due to norminette restriction presence of quotes is checked using
 a different function*/
void	ft_check_if_quote(char *s, int i, int *qval, int *openq)
{
	int	quote_value;
	int	open_quote;

	/*since we cannoot return mutliple variable values, we have passed the
	variables here as pointer so assigning them here will reflect on the 
	parent function */
	quote_value = *qval;
	open_quote = *openq;
	//quote_value is changed only on first encounter of a quote
	// hence the check quote_value == 0
	if ((s[i] == '\'' || s[i] == '\"') && quote_value == 0)
		quote_value = s[i];
	//each time it encounters the same quote we increment value
	if (s[i] == quote_value)
		open_quote += 1;
	//when 2 quotes are encountered open_quote becomes 2
	//therefore change open_quote to 0 indicating quotes have been closed
	if (open_quote % 2 == 0 && open_quote > 0)
	{
		quote_value = 0;
		open_quote = 0;
	}
	*qval = quote_value;
	*openq = open_quote;
}

/*	Due to norminette restrictions initializing the variables
	in a different function*/
void	ft_init_var_zero(int *i, int *j, int *q0, int *q1)
{
	*i = 0;
	*j = 0;
	*q0 = 0;
	*q1 = 0;
}

/*	Count number of tokens
	1.	Split is done on the basis of spaces and tabs
	2.	Inside quotes, spaces and tabs are not considered */
int	ft_count_tokens(char *s)
{
	int	words;
	int	i;
	int	quote_value; // to store which quote is open 39-single, 34-double quote
	int	open_quote; // to indicate an open quote. if 0(no quote open), if 1(one quote is open)

	//initialize separately due to norminette restriction
	ft_init_var_zero(&words, &i, &quote_value, &open_quote);
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
				ft_check_if_quote(s, i, &quote_value, &open_quote);
				i++;
			}
			// when the string terminates we check if any quotes are still open, indiacting error
			if (open_quote == 1)
				return (-1);
		}
		else
			i++; //skip to next character if space or tab
	}
	return (words);
}

/*split input string to tokens*/
void	ft_separate_tokens(char **t, char *s, int c)
{
	int	i;
	int	j;
	int	start; // starting index of each token
	int	len; // to store length of token to be extracted
	int	q[2];
	/*q[0] - to store value of the quote (39-single quote, 34-double quote*/
	/*q[1] - to inidcate an open quote, if 0(no quote open), if 1(one quote is open) */

	//initialize separately due to norminette restriction
	ft_init_var_zero(&i, &j, &q[0], &q[1]);
	//same logic as ft_count_tokens but here we count the characters and extract the substring
	// same concept of ft_split
	while (s[i])
	{
		if (s[i] != '\t' && s[i] != ' ' && s[i] != '\0')
		{
			start = i;
			len = 0;
			while (((s[i] != '\t' && s[i] != ' ') || q[1] == 1) && s[i])
			{
				ft_check_if_quote(s, i, &q[0], &q[1]);
				i++;
				len++;
			}
			t[j++] = ft_substr(s, start, len);
		}
		else
			i++;
	}
	t[j] = NULL;
}

/*	Count number of tokens so memory can be allocated
	Next split the input string into tokens.*/
void	ft_lexer(char *input, t_var	*vars)
{
	int		count;
	char	**tokens;

	if (!input)
		return ;
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
	// printf("====AFTER TOKEN SPLIT====\n");
	// ft_print_tokens(tokens);
	ft_expander(tokens, vars);
	// printf("====AFTER EXPANSION====\n");
	// ft_print_tokens(tokens);
	tokens = ft_split_redirection_pipe(tokens);
	if (tokens == NULL)
	{
		ft_free_tokens(tokens);
	}
	ft_parser(tokens, vars);
}
