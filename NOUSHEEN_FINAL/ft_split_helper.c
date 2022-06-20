/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 05:33:08 by nali              #+#    #+#             */
/*   Updated: 2022/06/16 08:51:59 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- CHECK COUNT OF CONSECUTIVE SYMBOLS ------------*/
/*	When encountering consecutive symbols check their count.
	If 2(in case of pipes) or more(<,>) consecutive symbols 
	gives syntax error*/
/*	- i is 1 coz we enter this function only when we encounter
	a symbol.
	- Now check how many repetitions are there for each symbol
	- In case of '|', if more than one pipe appears consecutively, then
	give syntax error.
	- In case of < and >,if more than 2 consecutive symbols appear consecutively
	then dispaly error*/
int	ft_check_symbols(char *str, int *index, int count)
{
	int	j;
	int	i;

	i = 1;
	j = *index;
	while (str[j] && str[j + 1] && str[j] == str[j + 1])
	{
		i++;
		j++;
	}
	*index = j;
	if (i > 2 || (i > 1 && str[j] == '|'))
	{
		printf("minishell: Syntax Error\n");
		g_err = 1;
		return (-1);
	}
	return (count + 1);
}

/*------------- CHECK IF QUOTE IS OPEN -------------*/
/*	If quote is open,  split will not be performed and characters will
	be skipped till end of quote or end of string*/
void	ft_handle_non_symbols(char *token, int *j, int *qv, int *open_quote)
{
	ft_check_if_quote(token, *j, qv, open_quote);
	if (*qv == 34 || *qv == 39)
		ft_skip_till_next_quote(token, j, qv, open_quote);
	else
		*j = *j + 1;
}

/*------------- INITIALIZE VARIABLES -------------*/
void	ft_init_var_split_count(int *i, int *count, int *qv, int *open_quote)
{
	*i = -1;
	*count = 0;
	*qv = 0;
	*open_quote = 0;
}

/*------------- COUNT NUMBER OF NEW TOKENS -------------*/
/*	Count number of new tokens if we split on basis of symbols |, <, >
	to allocate memory*/
/*	Important thing to note is that, the split will not be performed if
	if symbols appear inside single quotes or double quotes*/
/* 	Steps
	- If we encounter non symbols we increment count indicating start of a word
	- Skip till next symbol(<,>,|)
	- On encountering a symbol we see how many consecutive symbols of same type
	are present.
		example: >>, >, <<, <, | are acceptable
		example: ||, <<<, |||, >>> not acceptable
	- In the loop when the tokens[i][j] == NULL we decrement value of j to 
		avoid exception in the while condition(which again increments j)*/
int	ft_split_count(char **tokens)
{
	int	i;
	int	j;
	int	count;
	int	qv;
	int	open_quote;

	ft_init_var_split_count(&i, &count, &qv, &open_quote);
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
		{
			if (ft_strchr(">|<", tokens[i][j]) == NULL)
				count++;
			while (ft_strchr(">|<", tokens[i][j]) == NULL && tokens[i][j])
				ft_handle_non_symbols(tokens[i], &j, &qv, &open_quote);
			if (ft_strchr(">|<", tokens[i][j]) != NULL && tokens[i][j])
				count = ft_check_symbols(tokens[i], &j, count);
			if (count == -1)
				return (-1);
			if (!tokens[i][j])
					j--;
		}
	}
	return (count);
}
