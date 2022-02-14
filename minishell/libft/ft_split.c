/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:06:15 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/09 00:28:12 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getnumword(char const *s, char limit)
{
	size_t	i;

	i = 0;
	if (*s != limit && *s)
		i++;
	while (*(s + 1))
	{
		if (*s == limit && *(s + 1) != limit && *(s + 1) != '\0')
			i++;
		s++;
	}
	return (i);
}

static void	freezer(char **aux, int lap)
{
	int	i;

	i = lap;
	while (i-- > 0)
		free (aux[i]);
	free(aux);
	return ;
}

static void	storagewords(char **str, char **auxi, char c, int getword)
{
	int		j;
	char	*aux;

	j = 0;
	if (getword != 0 && **str)
	{
		while (**str == c)
		{
			j++;
			*str = *str + 1;
		}
		aux = ft_strchr(*str, c);
		*auxi = ft_substr(*str, 0, aux - *str);
		j = 0;
		while (j < aux - *str)
			*str = *str + 1;
	}
}

static char	**emptymat(void)
{
	char	**aux;

	aux = (char **) ft_calloc(1, sizeof(char *));
	if (!aux)
		return (NULL);
	aux[0] = 0;
	return (aux);
}

char	**ft_split(char const *s, char c)
{
	char	**aux;
	char	*str;
	int		n_words;
	int		i;

	i = -1;
	aux = NULL;
	if (!s || ft_strlen(s) == 0)
		return (emptymat());
	str = (char *)s;
	n_words = getnumword(str, c);
	aux = ft_calloc(n_words + 1, sizeof(char *));
	if (!aux)
		return (NULL);
	while (++i < n_words)
	{
		storagewords(&str, &(aux[i]), c, n_words);
		if (!aux[i])
		{
			freezer (aux, i);
			return (NULL);
		}
	}
	return (aux);
}
