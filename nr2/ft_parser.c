/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:08:32 by nali              #+#    #+#             */
/*   Updated: 2022/06/07 20:11:31 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  Stores token into list format*/

void	ft_parser(char **tokens, t_var *vars)
{
	/*store the list of commands into a list*/
	ft_create_list(tokens, vars);
	/*once list is created we do not need the tokens*/
	ft_free_tokens(tokens);
	//to print list
	ft_print_list(vars->cmd_lst);
	// if(built_in1(vars->cmd_lst->cmd, vars->env_var))
	// 	built_in2(vars->cmd_lst->cmd, vars->env_var);
	// else
	// 	printf("pipex");
	// exit(err_code);
}