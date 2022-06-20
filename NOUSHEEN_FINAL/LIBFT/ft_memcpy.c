/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:36:14 by nali              #+#    #+#             */
/*   Updated: 2021/11/02 20:36:14 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*memdest;
	const char		*memsrc;

	memdest = dest;
	memsrc = src;
	if (memdest == (unsigned char *)memsrc)
		return (memdest);
	while (n > 0)
	{
		*memdest = *memsrc;
		memdest++;
		memsrc++;
		n--;
	}
	return (dest);
}
