/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:56:20 by jporta            #+#    #+#             */
/*   Updated: 2022/02/24 17:45:10 by jsanfeli         ###   ########.fr       */
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
		while(line[i][j] != ' ' && line[i][j])
			j++;
		com[i].args = ft_substr(line[i], j + 1, ft_strlen(line[i]));
		i++;
	}
}
//"hola" "|" | pepe "|"
