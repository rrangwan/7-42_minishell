/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:08:32 by nali              #+#    #+#             */
/*   Updated: 2022/06/08 10:48:15 by nali             ###   ########.fr       */
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
	if(built_in1(vars->cmd_lst->cmd, vars))
		built_in2(vars->cmd_lst->cmd, vars);
	else
		printf("pipex");
	exit(err_code);
	ft_free_list(vars);
}
