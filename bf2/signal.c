/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 08:26:18 by rrangwan          #+#    #+#             */
/*   Updated: 2022/06/17 09:09:52 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//#define SIGQUIT 3 // CTRL + D = SIGQUIT / Quit the shell
//#define SIGINT 2 // CTRL + C = SIGINT / interrupt
// CTRL + \ = Does nothing
void	ft_sig(int sig)
{
	if (sig == SIGINT)
	{
		//printf("%c[K\n", 27); //ESC character
		//rl_replace_line("", 0); //replace last item in buff with in this case nothing
		//rl_on_new_line(); //tell buff we have moved to newline
		//rl_redisplay(); //change whats displayed on screen to whats in current readline buff
		g_err = 130;
		ft_putchar_fd('\n', 1);
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_err = 131;
		exit(g_err);
	}
}
/*
void	ft_sig2(int sig) //when in pipex child
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0); //replace last item in buff with in this case nothing
		rl_on_new_line(); //tell buff we have moved to newline
		rl_redisplay(); //change whats displayed on screen to whats in current readline buff
		g_err = 130;
		printf("testtttttinggw2222\n");
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: \n", 2);
		g_err = 131;
		exit(g_err);
	}
}
*/
