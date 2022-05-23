/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:10:55 by nali              #+#    #+#             */
/*   Updated: 2021/11/08 14:10:55 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		l;
	char	*result;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	l = ft_strlen((char *)s);
	result = (char *)malloc((l + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (i < l)
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
