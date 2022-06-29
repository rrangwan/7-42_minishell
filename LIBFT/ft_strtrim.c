/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:56:34 by nali              #+#    #+#             */
/*   Updated: 2021/11/07 12:56:34 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*ptr;

	i = 0;
	k = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr((char *)set, s1[i]) && s1[i])
		i++;
	j = ft_strlen((char *)s1);
	while (ft_strchr((char *)set, s1[j - 1]) && j > 0 && j > i)
		j--;
	ptr = (char *)malloc((j - i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < j)
	{
		ptr[k] = s1[i];
		k++;
		i++;
	}
	ptr[k] = '\0';
	return (ptr);
}
