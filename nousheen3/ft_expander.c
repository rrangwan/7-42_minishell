/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:36:30 by nali              #+#    #+#             */
/*   Updated: 2022/06/07 22:54:11 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	if single quote is open we do not want any substitution to happen even if
	even if there is a double quoted $VAR. Therefore, we have to skip the 
	characters till end of single quote.
	example: '${SHELL} "${SHELL}"' 	-> gives output -> ${SHELL} "${SHELL}"*/
void	ft_skip_till_next_quote(char *s, int *j, int *qval, int *open_quote)
{
	int	i;

	i = *j;
	i++;
	while (s[i] != 39 && s[i])
		i++;
	*qval = 0;
	*open_quote = 0;
	*j = i;
}

/*	Due to norminette restriction using separate function to 
	initialize variables*/
void	init_expander_var(int *i, int *qval, int *open_quote)
{
	*i = -1;
	*qval = 0;
	*open_quote = 0;
}

/*	Expander looks for environment variables, and substitues it with their values
	Variables are represented as $VAR or ${VAR}.
	$VAR or ${VAR} is not expanded if they appear inside single quotes.*/
void	ft_expander(char **t, t_var *vars)
{
	int		i;
	int		j;
	char	*sub;
	int		qv;// to store which quote is open 39-single, 34-double quote
	int		open_quote;// to indicate an open quote. if 0(no quote open), if 1(one quote is open)

	init_expander_var(&i, &qv, &open_quote);//initializing vars separately coz of norminette
	while (t[++i])
	{
		j = -1;
		while (t[i][++j])
		{
			//use the exact same logic as ft_count_tokens to check for quotes
			ft_check_if_quote(t[i], j, &qv, &open_quote);
			//if single quote, no expansion is done. Skip characters till
			// appearance of next single quote i.e., the closing quote
			if (t[i][j] == '$' && qv == 39)
				ft_skip_till_next_quote(t[i], &j, &qv, &open_quote);
			//if $ appears outside of single quote perform expansion 
			if (t[i][j] == '$' && t[i][j + 1] && (qv == 0 || qv == 34))
			{
				// get the string with expanded variable
				sub = ft_handle_dollar(t[i], j + 1, vars);
				//free the token value and replace with new expanded string
				free(t[i]);
				t[i] = sub;
				if (sub == NULL)
					break ;
			}
		}
	}
}
