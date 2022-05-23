/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:27:00 by nali              #+#    #+#             */
/*   Updated: 2021/11/07 12:27:00 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_copy(const char *s, unsigned int start, size_t len, size_t i)
{
	char	*str;

	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[start] && i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	l;

	i = 0;
	if (!s || len == 0)
	{
		ptr = ft_strdup("\0");
		return (ptr);
	}
	l = (size_t)ft_strlen((char *)s);
	if (start > l)
	{
		ptr = ft_strdup("\0");
		return (ptr);
	}
	if ((start + len) > l)
		len = l;
	ptr = ft_copy(s, start, len, i);
	return (ptr);
}
