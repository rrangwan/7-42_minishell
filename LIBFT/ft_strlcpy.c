/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:26:18 by nali              #+#    #+#             */
/*   Updated: 2021/11/09 12:49:19 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_len(const char *s)
{
	int	j;

	j = 0;
	while (s[j])
	{
		j++;
	}
	return (j);
}

unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int dstsize)
{
	int	i;
	int	slen;

	i = 0;
	slen = ft_len(src);
	if (dstsize > 0)
	{
		while (src[i] && dstsize - 1)
		{
			dst[i] = src[i];
			i++;
			dstsize--;
		}
		dst[i] = '\0';
	}
	return (slen);
}
