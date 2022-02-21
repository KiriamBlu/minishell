/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:56:20 by jporta            #+#    #+#             */
/*   Updated: 2022/02/21 20:48:41 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_comsize(char *line)
{
	int	i;
	int	a;

	a = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			while (line[++i] != '"')
				;
			i++;
		}
		else if (line[i] == '\'')
		{
			while (line[++i] != '\'')
				;
			i++;
		}
		if (line[i] == '|')
			a++;
		i++;
	}
	return (a);
}

char	**ft_prepare(char *line)
{
	int		j;
	char	**cmd;

	j = ft_comsize(line);
	j++;
	if ((ft_strchr(line, '|')) != NULL && j > 1)
		cmd = ft_splitmod(line, '|');
	else
	{
		cmd = malloc(sizeof(char *) * 1);
		cmd[0] = ft_strdup(line);
	}
	return (cmd);
}

//"hola" "|" | pepe "|"