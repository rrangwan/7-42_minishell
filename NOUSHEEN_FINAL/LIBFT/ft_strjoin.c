/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:40:16 by nali              #+#    #+#             */
/*   Updated: 2022/05/26 08:57:47 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

static char	*ft_string_copy(char const *s1, char const *s2, char *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
		{
			p[i] = s1[i];
			i++;
		}
	}
	if (s2)
	{
		while (s2[j])
		{
			p[i] = s2[j];
			j++;
			i++;
		}
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		l;

	l = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = (char *)malloc((l + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr = ft_string_copy(s1, s2, ptr);
	return (ptr);
}
