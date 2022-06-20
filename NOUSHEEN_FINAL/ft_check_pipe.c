/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:32:40 by nali              #+#    #+#             */
/*   Updated: 2022/06/14 09:15:36 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---------- APPEND NEWLINE TO STRING ----------*/
char	*ft_add_newline(char *buf)
{
	char	*str;

	if (!*buf)
	{
		free(buf);
		buf = (char *)malloc(2);
		buf[0] = '\n';
		buf[1] = '\0';
		return (buf);
	}
	str = ft_strjoin(buf, "\n");
	free(buf);
	return (str);
}

/*--------- READS INPUT FROM USER TILL LAST CHARACTER IS NOT A PIPE ---------*/
/*	We need to append '\n' to input string for the purpose of add_history().
	Because when displaying history it has to display the '\n' also */
/* 	while (buf[l] == '\n')
	we have used a while condition (instead of an if condition) beacuse when
	an empty string is read, a newline character is added each time at the 
	end. So, we will have to skip all new lines*/
char	*ft_get_input(char *buf)
{
	int		l;
	int		flag;
	char	*str;

	flag = 1;
	buf = ft_add_newline(buf);
	while (flag)
	{
		str = readline("pipe>");
		str = ft_add_newline(str);
		buf = ft_strjoin_new(buf, str);
		l = ft_strlen(buf) - 1;
		while (buf[l] == '\n')
			l--;
		while ((buf[l] == '\t' || buf[l] == ' ') && l > 0)
			l--;
		if (buf[l] != '|')
			flag = 0;
	}
	return (buf);
}

// /*--------- CHECKS IF FIRST AND LAST CHAR OF INPUT IS NOT A PIPE ---------*/
// /* 	This function checks if the input command ends with a 'pipe', if yes
// 	the program will prompt the user for additional characters input */
// /* 	A command also cannot start with a pipe, in which case it gives a 
// 	parse error. We are freeing and malloc again with null charcter here
// 	coz we dont want add_history() to add the command in case of parse error*/
// /* we may have cases where there will be spaces and tabs after |
// 	but no characters, so first we need to skip '\n' and 't' and
// 	check for the last non-space non-tab character if it is a pipe*/
char	*ft_check_pipe(char *buf)
{
	int		l;

	l = ft_strlen(buf);
	if (l == 0)
		return (buf);
	if (buf[0] == '|')
	{
		printf("minishell: parse error near `|'\n");
		g_err = 1;
		free(buf);
		buf = (char *)malloc(1);
		if (!buf)
		{
			ft_malloc_error();
			return (NULL);
		}
		buf[0] = '\0';
		return (buf);
	}
	l--;
	while ((buf[l] == '\t' || buf[l] == ' ') && l > 0)
		l--;
	if (buf[l] == '|')
		buf = ft_get_input(buf);
	return (buf);
}
