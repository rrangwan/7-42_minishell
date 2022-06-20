/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:31:12 by nali              #+#    #+#             */
/*   Updated: 2021/11/10 16:31:12 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!(*s))
		return (0);
	while (*s == (char)c)
		s++;
	while (s[j])
	{
		if (s[j] == (char)c && s[j - 1] != (char)c && j != 0)
			i++;
		j++;
	}
	if (s[j - 1] != c)
		i++;
	return (i);
}

static char	**ft_split_2(char const *s, char c, char **result, int w)
{
	int	len;
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i] && j < w)
	{
		while (s[i] == c)
			i++;
		start = i;
		len = 0;
		while (s[i] != c && s[i] != '\0')
		{
			len++;
			i++;
		}
		result[j] = ft_substr(s, start, len);
		j++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		w;

	if (!s)
	{
		result = (char **)malloc(sizeof(char));
		if (!result)
			return (NULL);
		return (&result[0]);
	}
	w = ft_count_words(s, c);
	result = (char **)malloc((w + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	ft_split_2(s, c, result, w);
	return (result);
}
