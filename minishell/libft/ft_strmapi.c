/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:48:51 by jsanfeli          #+#    #+#             */
/*   Updated: 2021/09/23 19:03:29 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			l;
	char			*str;
	char			*aux;

	if (!s || !f)
		return (NULL);
	l = ft_strlen(s);
	aux = ft_calloc(l + 1, sizeof(*aux));
	if (!aux)
		return (NULL);
	str = aux;
	i = -1;
	while (++i < l && str)
		*str++ = (*f)(i, *(s + i));
	return (aux);
}
