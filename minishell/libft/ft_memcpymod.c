/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpymod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:14:54 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/10 20:06:00 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpymod(void *dest, const void *src, size_t len)
{
	char		*d;
	char		*s;

	if (len == 0 || src == dest)
		return (dest);
	d = dest;
	s = (char *) src;
	while (len--)
	{
		if (*s == '"')
			s++;
		else if (*s == '\'')
			s++;
		*d++ = *s++;
	}
	return (dest);
}
