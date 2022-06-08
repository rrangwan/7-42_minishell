/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:30:40 by nali              #+#    #+#             */
/*   Updated: 2022/06/07 23:01:52 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (1);
	else
		return (0);
}

void	ft_print_list(t_cmd *cmd_lst)
{
	int		i;
	t_cmd *current;

	i = 0;
	if (cmd_lst == NULL)
		return ;
	current = cmd_lst;
	while (current)
	{
		i = 0;
		while (current->cmd[i])
		{
			printf("%s ", current->cmd[i]);
			i++;
		}
		printf("\n");
		current = current->next;
	}
}

void	ft_print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	printf("---------------\n");
}
