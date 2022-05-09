/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpymod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:14:54 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/15 17:21:53 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memcpymod(char *dest, char *src)
{
	size_t		i;

	if (ft_strlen(src) == 0 || src == dest)
		return (dest);
	i = 0;
	while (i < ft_strlen(src))
	{
		if (src[i] == '"')
			while (src[++i] != '"' && src[i] != '\0')
				dest[i] = src[i];
		else if (src[i] == '\'' && src[i] != '\0')
			while (src[++i] != '\'')
				dest[i] = src[i];
		else if (src[i] != '\0')
			dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
