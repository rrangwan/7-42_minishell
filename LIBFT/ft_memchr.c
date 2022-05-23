/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:34:01 by nali              #+#    #+#             */
/*   Updated: 2021/11/02 21:34:01 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*mem;

	mem = s;
	while (n > 0)
	{
		if (*mem == (char)c)
			return ((void *)mem);
		mem++;
		n--;
	}
	return (NULL);
}
