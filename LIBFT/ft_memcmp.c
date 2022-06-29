/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:11:17 by nali              #+#    #+#             */
/*   Updated: 2021/11/02 21:11:17 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*mems1;
	const char	*mems2;

	mems1 = s1;
	mems2 = s2;
	while (n > 0)
	{
		if (*mems1 != *mems2)
			return (*(unsigned char *)mems1 - *(unsigned char *)mems2);
		mems1++;
		mems2++;
		n--;
	}
	return (0);
}
