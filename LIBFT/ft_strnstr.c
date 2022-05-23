/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:11:09 by nali              #+#    #+#             */
/*   Updated: 2021/11/06 17:11:09 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(const char *str, const char *substr, size_t n)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = (size_t)ft_strlen((char *)substr);
	if (n < l)
		return (0);
	while (str[i] && substr[i])
	{
		if (str[i] != substr[i])
			return (0);
		else
			i++;
	}
	return (1);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (*s2 == '\0' || s2 == NULL)
		return ((char *)s1);
	if (n == 0)
		return (NULL);
	while (s1[i] && s2[j] && i < n)
	{
		if (s1[i] == s2[j])
		{
			if (ft_check(&s1[i], &s2[j], n - i))
				return ((char *)&s1[i]);
		}
		j = 0;
		i++;
	}	
	return (NULL);
}
