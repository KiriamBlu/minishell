/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinmod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:52:09 by jporta            #+#    #+#             */
/*   Updated: 2022/05/04 19:58:41 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoinmod(char *line, char c)
{
	char *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!line)
	{
		tmp = (char *)malloc(2);
		tmp[0] = c;
		tmp[1] = 0;
	}
	else
	{
		while(line[i])
			i++;
		tmp = (char*)malloc(i + 2);
		while (j < i)
		{
			tmp[j] = line[j];
			j++;
		}
		tmp[j] = c;
		tmp[j + 1] = 0;
		free(line);
	}
	return(tmp);
}