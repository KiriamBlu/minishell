/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parshe0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:56:20 by jporta            #+#    #+#             */
/*   Updated: 2022/02/17 19:04:16 by jporta           ###   ########.fr       */
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

void	ft_parshe(char *line)
{
	int		i;
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
	i = -1;
	while (cmd[++i])
		printf("%s\n", cmd[i]);
	freemat(cmd);
}

//"hola" "|" | pepe "|"