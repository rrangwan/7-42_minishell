/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:08:17 by nali              #+#    #+#             */
/*   Updated: 2022/06/17 08:47:04 by rrangwan         ###   ########.fr       */
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
	vars->env_var[i] = NULL;
}

void	ft_free_env(t_var *vars)
{
	int	i;

	i = 0;
	while (vars->env_var[i])
	{
		free(vars->env_var[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	char	**cmd;
	t_var	vars;

	if (argc == 1 && !argv[1])
	{
		ft_init_vars(&vars, envp);
		while (1)
		{
			signal(SIGQUIT, ft_sig);
			signal(SIGINT, ft_sig);
			buf = readline(vars.prompt);
			if (buf != NULL)
			{
				add_history(buf);
				cmd = ft_split(buf, ' ');
				if (built_in1(cmd, &vars))
					built_in2(cmd, &vars);
				else
				{
					//signal(SIGQUIT, ft_sig2);
					//signal(SIGINT, ft_sig2);
					printf("pipex\n");
				}
				free(buf);
			}
			else
				break ;
		}
		ft_free_env(&vars);
	}
	return (0);
}
