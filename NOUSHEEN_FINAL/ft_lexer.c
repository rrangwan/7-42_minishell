/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 04:55:03 by nali              #+#    #+#             */
/*   Updated: 2022/06/17 16:43:45 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- GETS QUOTE VALUE IF QUOTE IS OPEN -------------*/
/* 	due to norminette restriction presence of quotes is checked using
 	a different function*/
/*	since we cannot return mutliple variable values, we have passed the
	variables here as pointer so assigning them here will reflect on the 
	parent function */
/* 	quote_value is changed only on first encounter of a quote hence the 
	check quote_value == 0
	
	Each time it encounters the same quote in the string we increment value
	of open_quoteby 1.

	when 2 quotes(of same type) are encountered open_quote becomes 2
	Then change open_quote to 0 indicating quotes have been closed*/
void	ft_check_if_quote(char *s, int i, int *qval, int *openq)
{
	int	quote_value;
	int	open_quote;

	quote_value = *qval;
	open_quote = *openq;
	if ((s[i] == '\'' || s[i] == '\"') && quote_value == 0)
		quote_value = s[i];
	if (s[i] == quote_value)
		open_quote += 1;
	if (open_quote % 2 == 0 && open_quote > 0)
	{
		quote_value = 0;
		open_quote = 0;
	}
	*qval = quote_value;
	*openq = open_quote;
}

/*------------- COUNT TOKENS FOR SPLIT -------------*/
/*	Count number of tokens
	1.	Split is done on the basis of spaces and tabs
	2.	Inside quotes, spaces and tabs are not considered */
/*	quote_value - to store which quote is open 39-single, 34-double quote
	open_q - indicates an open quote.0(no quote open),1(one quote is open)*/
/*	Two cases the loop after words++ is executed
	1. till a tab or space or newline is encountered
	2. we have an open quote in which case we dont check for tab or space
	at the same time check if we reached end of string*/
/* 	if (open_q == 1) -- when the string terminates we check if any quotes are 
	still open, indiacting error*/
int	ft_count_tokens(char *s)
{
	int	words;
	int	i;
	int	quote_value;
	int	open_q;

	ft_init_var_zero(&words, &i, &quote_value, &open_q);
	while (s[i])
	{
		if (s[i] != '\t' && s[i] != ' ' && s[i] != '\n' && s[i] != '\0')
		{
			words++;
			while ((ft_chk_not_space_tab_newline(s[i]) || open_q == 1) && s[i])
			{
				ft_check_if_quote(s, i, &quote_value, &open_q);
				i++;
			}
			if (open_q == 1)
				return (-1);
		}
		else
			i++;
	}
	return (words);
}

/*------------- SPLIT INPUT STRING TO TOKENS -------------*/
/*	splits incoming string into tokens either based on spaces or
	(single/double) quotes*/
/*	start - starting index of each token
	len - to store length of token to be extracted
	q[0] - to store value of the quote (39-single quote, 34-double quote
	q[1] - to inidcate an open quote, 0(no quote open), 1(one quote is open)*/
/* 	same logic as ft_count_tokens but here we count the characters and
	extract the substring(same concept of ft_split)*/
void	ft_separate_tokens(char **t, char *s)
{
	int	i;
	int	j;
	int	start;
	int	len;
	int	q[2];

	ft_init_var_zero(&i, &j, &q[0], &q[1]);
	while (s[i])
	{
		if (s[i] != '\t' && s[i] != ' ' && s[i] != '\n' && s[i] != '\0')
		{
			start = i;
			len = 0;
			while ((ft_chk_not_space_tab_newline(s[i]) || q[1] == 1) && s[i])
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

/*------------- SPLIT, EXPAND,SEGGREGATE AND TRIM TOKENS -------------*/
void	ft_lexer_2(char *input, t_var	*vars, char **tokens)
{
	char	**new_tokens;

	ft_separate_tokens(tokens, input);
	if (!*tokens)
	{
		ft_free_tokens(tokens);
		return ;
	}
	ft_expander(tokens, vars);
	new_tokens = ft_split_redirection_pipe(tokens);
	if (new_tokens == NULL)
	{
		ft_free_tokens(tokens);
		return ;
	}
	ft_parser(new_tokens, vars);
}

/*------------- COUNT TOKENS AND ALLOCATE MEMORY -------------*/
/*	Count number of tokens so memory can be allocated.*/
void	ft_lexer(char *input, t_var	*vars)
{
	int		count;
	char	**tokens;

	if (!*input || !input)
		return ;
	count = ft_count_tokens(input);
	if (count == -1)
	{
		printf("minishell: Invalid Quotes\n");
		g_err = 1;
		return ;
	}
	tokens = (char **)malloc((count + 1) * sizeof(char *));
	if (!tokens)
	{
		ft_malloc_error();
		return ;
	}
	ft_lexer_2(input, vars, tokens);
}
