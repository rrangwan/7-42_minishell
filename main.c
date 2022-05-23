/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:00:55 by nali              #+#    #+#             */
/*   Updated: 2022/05/23 11:03:51 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
realine() - Reads the command from user till newline
add_history - Adds to the history of commands
*/
/*following linkers required to execute the program
gcc minishell.c -L/usr/local/lib -I/usr/local/include -lreadline */

int	main(void)
{
	char	*buf;
	char	prompt[2];

	prompt[0] = '>';
	prompt[1] = '\0';
	while (1)
	{
		buf = readline(prompt);
		if (buf != NULL)
		{
			if (ft_strcmp(buf, "exit") == 1)
			{
				free(buf);
				return (0);
			}
			if (*buf)
				add_history(buf);
			ft_lexer(buf);
			free(buf);
		}
	}
	return (0);
}
