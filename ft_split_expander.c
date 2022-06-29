/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 06:40:01 by nali              #+#    #+#             */
/*   Updated: 2022/06/23 22:47:16 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  After expansion check if need to split again
	This need to be done before we trim quotes*/

#include "minishell.h"

void	ft_copy_tokens(char **new_tokens, int index, char **tokens, char **str)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (++i < index)
	{
		new_tokens[i] = ft_strdup(tokens[k]);
		k++;
	}
	j = -1;
	while (str[++j])
	{
		new_tokens[i] = ft_strdup(str[j]);
		i++;
	}
	k++;
	while (tokens[k])
	{
		new_tokens[i] = ft_strdup(tokens[k]);
		i++;
		k++;
	}
	new_tokens[i] = NULL;
}

char	**ft_split_tokens_again(char **tokens, int index, int count)
{
	int		l;
	char	**new_tokens;
	char	**str;

	str = (char **)malloc((count + 1) * sizeof(char *));
	if (!str)
	{
		ft_malloc_error();
		return (NULL);
	}
	ft_separate_tokens(str, tokens[index]);
	l = 0;
	while (tokens[l])
		l++;
	new_tokens = (char **)malloc((l + count) * sizeof(char *));
	if (!new_tokens)
	{
		ft_free_array(str);
		ft_malloc_error();
		return (NULL);
	}
	ft_copy_tokens(new_tokens, index, tokens, str);
	ft_free_tokens(tokens);
	ft_free_array(str);
	return (new_tokens);
}

/*------------- CHECK SPLIT AFTER EXPANSION -------------*/
/* This is for special case 
	export ll='ls -la'
	when we run the command $ll, the result should be that of 
	running ls -la command. If we do not split this again
	system will read command as ls -la(which does not exist).
	ls is the command and -la is an argument. 
	So after expansion check if there ia a space outside quote.
	If yes, split again.
	*/
char	**ft_split_expander(char **tokens)
{
	int		i;
	int		count;

	i = -1;
	if (!tokens || !*tokens)
		return (NULL);
	while (tokens[++i])
	{
		count = ft_count_tokens(tokens[i]);
		if (count > 1)
		{
			tokens = ft_split_tokens_again(tokens, i, count);
			if (tokens == NULL)
			{
				ft_free_tokens(tokens);
				return (NULL);
			}
			i = -1;
		}
	}
	return (tokens);
}
