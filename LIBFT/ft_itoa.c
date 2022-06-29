/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:06:01 by nali              #+#    #+#             */
/*   Updated: 2022/05/10 14:19:56 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_findlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n = n * -1;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_converttostr(char *s, int n, int sign, int l)
{
	int	i;

	i = 0;
	if (sign == -1)
	{
		s[i] = '-';
		i++;
		n = n * sign;
	}
	s[l] = '\0';
	while (l > i)
	{
		l--;
		s[l] = n % 10 + '0';
		n = n / 10;
	}
	return (s);
}

static char	*ft_handle_exception(int n)
{
	char	*result;

	if (n == 0)
	{
		result = (char *)malloc(2 * sizeof(char));
		result[0] = '0';
		result[1] = '\0';
	}
	if (n == -2147483648)
	{
		result = (char *)malloc(12 * sizeof(char));
		result[0] = '-';
		result[1] = '2';
		ft_converttostr(&result[2], 147483648, 1, 9);
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*str;
	char	*result;
	int		l;
	int		sign;

	l = 0;
	sign = 1;
	if (n == 0 || n == -2147483648)
	{
		result = ft_handle_exception(n);
		return (result);
	}
	if (n < 0 && n != -2147483648)
	{
		l++;
		sign = -1;
	}
	l = l + ft_findlen(n);
	str = (char *)malloc((l + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str = ft_converttostr(str, n, sign, l);
	return (str);
}
