/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:19:58 by nali              #+#    #+#             */
/*   Updated: 2022/06/07 19:34:31 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*extract command between pipes*/

char	**ft_extract_sub_cmd(char **tokens, int start, int stop)
{
	char	**cmds;
	int		i;
	int		l;

	cmds = (char **)malloc((stop - start + 1) * sizeof(char *));
	if (!cmds)
	{
		printf("Insufficient Memory\n");
		return (NULL);
	}
	i = 0;
	while (start < stop)
	{
		l = ft_strlen(tokens[start]);
		cmds[i] = (char *)malloc(l + 1);
		if (!cmds[i])
			return (NULL);
		ft_strlcpy(cmds[i], tokens[start], l + 1);
		i++;
		start++;
	}
	cmds[i] = NULL;
	return (cmds);
}

/* allocates memory for a command node*/

t_cmd	*ft_create_node(char **tokens, int start, int stop, t_var *vars)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
	{
		printf("Insufficient Memory\n");
		return (NULL);
	}
	new->cmd = ft_extract_sub_cmd(tokens, start, stop);
	new->next = NULL;
	return (new);
}

void	ft_add_node(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current;

	current = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}
/* splits command on the basis of pipe
and stores it as a linked list*/

void	ft_create_list(char **tokens, t_var *vars)
{
	int		i;
	int		start;
	t_cmd	*node;

	i = 0;
	node = NULL;
	while (tokens[i])
	{
		start = i;
		while (tokens[i] && tokens[i][0] != '|')
			i++;
		node = ft_create_node(tokens, start, i, vars);
		ft_add_node(&vars->cmd_lst, node);
		// if (!tokens[i] || tokens[i][1])
		// 	break ;
		i++;
	}
}
