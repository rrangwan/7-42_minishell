/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42AbuDhabi.AE>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:00:55 by nali              #+#    #+#             */
/*   Updated: 2022/05/31 00:05:43 by rrangwan         ###   ########.fr       */
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

	//should be more obvious
	//changed in minishel.h, struct to:	char prompt[11];
	ft_strlcpy(vars->prompt, "minishell>", 11);
	i = 0;
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

//should not take any arguments, and no error message is given, simply terminated  (return 0)
	if (argc == 1 && !argv[1])
	{
		//add here signal functions
		ft_init_vars(&vars, envp);
		//endless loop, so use 1
		while (1)
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
			//to exit while loop if buff NULL
			else
				break ;
		}
		//add here free-funtions for ft_flexer stuff.
	}
	return (0);
}




/* old main.c
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

*/