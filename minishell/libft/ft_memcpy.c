/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:14:54 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/10 20:02:12 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	if (len == 0 || src == dest)
		return (dest);
	d = dest;
	s = src;
	while (len--)
		*d++ = *s++;
	return (dest);
}
