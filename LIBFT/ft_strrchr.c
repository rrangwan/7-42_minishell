/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 09:39:41 by nali              #+#    #+#             */
/*   Updated: 2021/11/18 09:48:22 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int	pos;
	int	i;

	i = 0;
	pos = -1;
	while (str[i])
	{
		if (str[i] == (char)c)
			pos = i;
		i++;
	}
	if (str[i] == c)
		return (&str[i]);
	if (pos != -1)
		return (&str[pos]);
	else
		return (NULL);
}
