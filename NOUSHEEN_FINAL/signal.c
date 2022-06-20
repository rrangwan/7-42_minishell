/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 08:26:18 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/20 11:24:14 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*------------- SIGNAL HANDLER -------------*/
/* 	SIGINT - ctrl + C
	SIGQUIT - ctrl + \
	ctrl + D- is not a signal. It is EOF */

void	ft_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		printf("minishell: Quit\n");
	}
}
