/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:06:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/17 19:03:47 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_c(char *str, char c)
{
	size_t	i;
	int		count;

	count = 0;
	i = 0;
	if (str[0] && str[0] != c)
		count++;
	while (i < ft_strlen(str))
	{
		if (str[i] == '"')
			while (str[++i] != '"' && str[i] != '\0')
				;
		else if (str[i] == '\'' && str[i] != '\0')
			while (str[++i] != '\'')
				;
		else if (str[i] == c && str[i + 1] && str[i + 1] != c)
			count ++;
		i++;
	}
	return (count);
}

static int	lengt(char const *s, char c, int aux)
{
	int	len;

	len = 0;
	while (s[aux] == c && s[aux])
		aux++;
	while (s[aux] != c && s[aux])
	{
		aux++;
		len++;
	}
	return (len);
}

char	**ft_splitmod(char *s, char c)
{
	int		index;
	int		i;
	int		aux;
	char	**split;

	i = 0;
	if (!s)
		return (0);
	split = ft_calloc(sizeof(char *), (count_c(s, c) + 1));
	if (!split)
		return (NULL);
	index = 0;
	aux = 0;
	while (index < count_c(s, c))
	{
		split[index] = ft_calloc(sizeof(char *), (lengt(s, c, aux) + 1));
		while (s[aux] != c && s[aux] != '\0' )
		{
			if (s[aux] == '"')
			{
				while (s[++aux] != '"' && s[aux] != '\0')
					split[index][i++] = s[aux];
				aux++;
			}
			else if (s[aux] == '\'')
			{
				while (s[++aux] != '\'' && s[aux] != '\0')
					split[index][i++] = s[aux];
				aux++;
			}
			split[index][i++] = s[aux++];
		}
		while (s[aux] == c && s[aux] != '\0')
		{
			if (s[aux + 1] == ' ')
				aux++;
			aux++;
		}
		split[index][i] = '\0';
		i = 0;
		index++;
	}
	return (split);
}
//------------------->errores<-------------------
//"hola '|' 'pepito' 'hola' " | cat
//"hola '|' 'pepito' 'pepito' " | cat | "hola "|" " mal
