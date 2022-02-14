/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parshe0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:56:20 by jporta            #+#    #+#             */
/*   Updated: 2022/02/14 15:49:22 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_comsize(char *line)
{
	int	i;
	int	a;

	a = 0;
	i = -1;
	while (line[++i])
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
	}
	return (a);
}

void	ft_parshe(char *line)
{
	t_cmds	*comands;
	int		i;
	int		j;
	char	**cmd;

	j = ft_comsize(line);
	j++;
	comands = malloc(sizeof(t_cmds) * j);
	if ((ft_strchr(line, '|')) != NULL)
		cmd = ft_splitmod(line, '|');
	else
	{
		cmd = malloc(sizeof(char *) * 1);
		cmd[0] = ft_strdupmod(line);
	}
/* 	i = -1;
	while (cmd[++i])
		printf("cmd :%s\n", cmd[i]);
	i = -1;
	while (cmd[++i])
	{
		comands[i].args = cmd[i];
		printf("comands: %s\n", comands[i].args);
	} */
	freemat(cmd);
}
