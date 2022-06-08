/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_redirection_pipe.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 09:23:04 by nali              #+#    #+#             */
/*   Updated: 2022/06/08 10:43:00 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	When encountering consecutive symbols check their count.
	More than 2 consecutive symbols gives syntax error*/
int	ft_check_symbols(char *str, int *index, int count)
{
	int	j;
	int	i; // to check count of consecutive symbols

	/*i is 1 coz we enter this function only when we encounter
	a symbol*/
	i = 1;
	j = *index;
	/*check how many repetitions are there for each symbol*/
	while (str[j] && str[j + 1] && str[j] == str[j + 1])
	{
		i++;
		j++;
	}
	*index = j;
	/* if more than 2 consecutive symbols of same kind then dispaly error*/
	if (i > 2)
	{
		printf("Syntax Error\n");
		return (-1);
	}
	return (count + 1);
}

/*	Count number of new tokens if we split on basis of symbols |, <, >
	to allocate memory*/
int	ft_split_count(char **tokens)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
		{
			//if we encounter non symbols we increment count
			//indicating start of a word
			if (ft_strchr(">|<", tokens[i][j]) == NULL)
				count++;
			//skip till next symbol(<,>,|)
			while (ft_strchr(">|<", tokens[i][j]) == NULL && tokens[i][j])
				j++;
			//on encountering a symbol we see how many consecutive symbols
			//of same type are present.
			// example: >>, >, <<, <, ||, | are acceptable
			// example: <<<, |||, >>> not acceptable
			if (ft_strchr(">|<", tokens[i][j]) != NULL && tokens[i][j])
				count = ft_check_symbols(tokens[i], &j, count);
			if (count == -1) 
				return (-1);
			// when the tokens[i][j] == NULL we decrement value of j to 
			// avoid exception in the while condition(which again increments j)
			if (!tokens[i][j])
				j--;
		}
	}
	return (count);
}

/*	extracts the words containing either only symbols or only non symbols
 	from token and populates new array*/
void	ft_populate_new_tokens(int *j, int *k, char **new_tokens, char *str)
{
	int	start;
	int	m;
	int	n;

	m = *j;
	n = *k;
	start = m;
	//if not a symbol
	if (ft_strchr(">|<", str[m]) == NULL && str[m])
	{
		while (ft_strchr(">|<", str[m]) == NULL && str[m])
			m++;
		//in the next line 3rd argument is m - start coz m is the
		// index of a symbol or NULL
		new_tokens[n] = ft_substr(str, start, m - start);
		n++;
	}
	start = m;
	//if a symbol
	if (ft_strchr(">|<", str[m]) != NULL && str[m])
	{
		while (str[m] == str[m + 1])
			m++;
		//in the next line 3rd argument is m - start + 1 coz m is the
		// index of last symbol
		new_tokens[n] = ft_substr(str, start, m - start + 1);
		n++;
	}
	*j = m;
	*k = n;
}

/* 	Once memory is allocated we can split the tokens if they 
	contain symbols <|> (Same logic of ft_split) */
char	**ft_perform_split(char **new_tokens, char **tokens)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			ft_populate_new_tokens(&j, &k, new_tokens, tokens[i]);
			if (!tokens[i][j])
				j--;
			j++;
		}
		i++;
	}
	new_tokens[k] = NULL;
	return (new_tokens);
}

/*	Splits the tokens again on the basis of pipes and redirections*/
//	EXAMPLE
/*	Incoming command : cat< 'file1'|grep '123' | wc >>file2
	In lexer tokens created by splitting on the basis of spaces and quotes
		tokens = {"cat<" , "'file1'|grep" , "'123'" , "|" , "wc", ">>file2"}

	In ft_separate_redirection_pipe new_tokens will look like
	new_tokens = {"cat", "<" , "'file1'" , "|", "grep" , "'123'", "|" , "wc" , ">>" , "file2"}

	After that, it trims the new tokens of any quotes. This is because, though shell syntax has
	quotes it cannot process quotes.*/
char	**ft_split_redirection_pipe(char **tokens)
{
	int		new_count;
	char	**new_tokens;

	new_count = ft_split_count(tokens);
	// printf("new count = %d\n", new_count);
	if (new_count == -1)
		return (NULL);
	new_tokens = (char **)malloc((new_count + 1) * sizeof(char *));
	if (!new_tokens)
	{
		printf("Insufficient Memory\n");
		return (NULL);
	}
	new_tokens = ft_perform_split(new_tokens, tokens);
	// printf("====AFTER SPLIT REDIRECTION PIPE====\n");
	// ft_print_tokens(new_tokens);
	ft_free_tokens(tokens);
	new_tokens = ft_trim(new_tokens);
	// printf("====AFTER TRIM====\n");
	// ft_print_tokens(new_tokens);
	return(new_tokens);
}