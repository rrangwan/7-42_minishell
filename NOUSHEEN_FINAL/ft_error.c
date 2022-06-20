/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:47:00 by nali              #+#    #+#             */
/*   Updated: 2022/06/13 06:26:21 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_error(void)
{
	printf("minishell: Insufficient Memory.\n");
	g_err = 1;
}

void	ft_parse_error(void)
{
	printf("minishell: Insufficient Memory.\n");
	g_err = 1;
}

void	ft_cmd_error(char *cmd)
{
	printf("minishell:  command not found: %s\n", cmd);
	g_err = 127;
}
