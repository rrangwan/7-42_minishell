/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_redirection_pipe.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 09:23:04 by nali              #+#    #+#             */
/*   Updated: 2022/06/17 16:42:24 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- INIT VARIABLES -------------*/
void	ft_init_populate(int *qv, int *open_quote)
{
	*qv = 0;
	*open_quote = 0;
}

/*------------- SEGGREGATE PIPES, REDIRECTIONS -------------*/
/*	extracts the words containing either only symbols or only non symbols
 	from token and populates new array*/
/*	Important thing to note is that, the split will not be performed if
	if symbols appear inside single quotes or double quotes*/
/*	If not a symbol --> ft_strchr(">|<", str[m]) == NULL
		new_tokens[n] = ft_substr(str, start, m - start);
		The third argument in ft_substr is m - start beacuse, m is the index
		of a symbol or NULL terminator
	If a symbol --> ft_strchr(">|<", str[m]) != NULL
		new_tokens[n] = ft_substr(str, start, m - start + 1);
		The 3rd argument in ft_substr is m - start + 1 coz  we are checking
		if (str[m] == str[m + 1]) and therefore we need to include m + 1 index also
		(which is the index of the last symbol)*/
void	ft_populate_new_tokens(int *j, int *k, char **new_tokens, char *str)
{
	int	start;
	int	m;
	int	n;
	int	qv;
	int	open_quote;

	m = *j;
	n = *k;
	start = m;
	ft_init_populate(&qv, &open_quote);
	if (ft_strchr(">|<", str[m]) == NULL && str[m])
	{
		while (ft_strchr(">|<", str[m]) == NULL && str[m])
			ft_handle_non_symbols(str, &m, &qv, &open_quote);
		new_tokens[n++] = ft_substr(str, start, m - start);
	}
	start = m;
	if (ft_strchr(">|<", str[m]) != NULL && str[m])
	{
		while (str[m] == str[m + 1])
			m++;
		new_tokens[n++] = ft_substr(str, start, m - start + 1);
	}
	*j = m;
	*k = n;
}

/*------------- SPLIT TOKENS -------------*/
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

/*------------ SPLITS TOKENS ON BASIS OF PIPES AND REDIRECTIONS ------------*/
//	EXAMPLE
/*	Incoming command : cat< 'file1'|grep '123' | wc >>file2*/
/*	In lexer tokens created by splitting on the basis of spaces and quotes
	tokens = {"cat<" , "'file1'|grep" , "'123'" , "|" , "wc", ">>file2"}*/

/*	In ft_separate_redirection_pipe new_tokens will look like
{"cat", "<" , "'file1'" , "|", "grep" , "'123'", "|" , "wc" , ">>" , "file2"}*/

/*	After that, it trims the new tokens of any quotes. This is because,
	though shell syntax has quotes it cannot process quotes.*/
char	**ft_split_redirection_pipe(char **tokens)
{
	int		new_count;
	char	**new_tokens;

	if (!tokens || !*tokens)
		return (NULL);
	new_count = ft_split_count(tokens);
	if (new_count == -1)
		return (NULL);
	new_tokens = (char **)malloc((new_count + 1) * sizeof(char *));
	if (!new_tokens)
	{
		ft_malloc_error();
		return (NULL);
	}
	new_tokens = ft_perform_split(new_tokens, tokens);
	ft_free_tokens(tokens);
	new_tokens = ft_trim(new_tokens);
	return (new_tokens);
}
