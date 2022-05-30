/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:00:55 by nali              #+#    #+#             */
/*   Updated: 2022/05/27 15:33:12 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
realine() - Reads the command from user till newline
add_history - Adds to the history of commands
*/
/*following linkers required to execute the program
gcc minishell.c -L/usr/local/lib -I/usr/local/include -lreadline */

void	ft_init_vars(t_var	*vars, char **envp)
{
	int	i;

	i = 0;
	vars->prompt[0] = '>';
	vars->prompt[1] = '\0';
	while (envp[i])
		i++;
	vars->env_var = (char **)malloc((i + 1) * sizeof(char *));
	if (!vars->env_var)
		return ;
	i = 0;
	while (envp[i])
	{
		vars->env_var[i] = ft_strdup(envp[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	t_var	vars;

	ft_init_vars(&vars, envp);
	while (argc && argv)
	{
		buf = readline(vars.prompt);
		if (buf != NULL)
		{
			if (ft_strcmp(buf, "exit") == 1)
			{
				free(buf);
				ft_free_env(&vars);
				return (0);
			}
			if (*buf)
				add_history(buf);
			ft_lexer(buf, vars);
			free(buf);
		}
	}
	return (0);
}
