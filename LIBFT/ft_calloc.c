/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 22:39:07 by nali              #+#    #+#             */
/*   Updated: 2021/11/06 22:39:07 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(nelem * elsize);
	if (!(ptr))
		return (NULL);
	while (i < (nelem * elsize))
	{
		ptr[i] = '\0';
		i++;
	}
	return ((void *)ptr);
}
