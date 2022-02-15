/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:01:53 by ifluxa-c          #+#    #+#             */
/*   Updated: 2021/09/24 12:43:29 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	b;
	size_t	len;

	a = ft_strlen(dst);
	len = ft_strlen(src);
	if (a > size)
		a = size;
	b = 0;
	while (src[b] && a + b + 1 < size)
	{
		dst[a + b] = src[b];
		b++;
	}
	if (b != 0)
		dst[a + b] = '\0';
	return (len + a);
}
