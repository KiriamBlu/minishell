/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:56:20 by jporta            #+#    #+#             */
/*   Updated: 2022/02/24 16:58:03 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_prepare(char *line)
{
	char	**cmd;

	if (ft_strchr(line, '|') != 0)
		cmd = ft_splitmod(line, '|');
	else
		cmd = ft_split(line, '|');
	return (cmd);
}

void	morfeo(t_cmds *com, char **line)
{
	int 	i;
	char	**aux;
	int		j;

	i = 0;
	while (line[i])
	{
		j = 0;
		aux = ft_split(line[i], ' ');
		com[i].cmd = ft_strdup(aux[0]);
		freemat(aux);
		while(line[i][j] == ' ')
			j++;
		while(line[i][j] != ' ')
			j++;
		printf("%d\n", j);
		com[i].args = ft_substr(line[i], j + 1, ft_strlen(line[i]));
		printf("%s\n%s\n", com[i].cmd, com[i].args);
		i++;
	}
	
}

//"hola" "|" | pepe "|"