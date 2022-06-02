/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:08:17 by nali              #+#    #+#             */
/*   Updated: 2022/06/02 18:21:20 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_vars(t_var	*vars, char **envp)
{
	int	i;

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

void	ft_free(char *buf, t_var *vars)
{
	free(buf);
	ft_free_env(vars);
}

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	t_var	vars;

	if (argc == 1 && !argv[1])
	{
		ft_init_vars(&vars, envp);
		while (1)
		{
			buf = readline(vars.prompt);
			if (buf != NULL)
			{
				if (ft_strcmp(buf, "exit") == 1)
				{
					ft_free(buf, &vars);
					return (0);
				}
				if (*buf)
					add_history(buf);
				ft_lexer(buf, &vars);
				free(buf);
			}
			else
				break ;
		}
		ft_free(buf, &vars);
	}
	return (0);
}