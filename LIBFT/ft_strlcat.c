/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:30:09 by nali              #+#    #+#             */
/*   Updated: 2021/11/07 10:30:09 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_findlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ld;
	size_t	ls;
	int		j;
	size_t	i;

	i = 0;
	while (dst[i] != '\0' && i < size)
		i++;
	ld = i;
	ls = ft_findlen(src);
	j = 0;
	if (size < ld + 1)
		return (size + ls);
	if (size == ld + 1)
		return (ld + ls);
	while (src[j] && ((ld + j) < (size - 1)))
	{
		dst[ld + j] = src[j];
		j++;
	}
	dst[ld + j] = '\0';
	return (ld + ls);
}
