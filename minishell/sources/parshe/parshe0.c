/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parshe0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:56:20 by jporta            #+#    #+#             */
/*   Updated: 2022/02/08 23:58:51 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_comsize(char *line)
{
	int	i;
	int	a;

	i = -1;
	a = 0;
	while (line[++i] == ';')
		a++;
	if (a > 0)
		return (a);
	i = -1;
	while (line[++i] == '|')
		a++;
	if (a == 0)
		a++;
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
	if (ft_strnstr(line, ";", ft_strlen(line)) != 0)
		cmd = ft_split(line, ';');
	else
		cmd = ft_split(line, '|');
	i = -1;
	while (cmd[++i])
		printf("%s\n", cmd[i]);
	i = -1;
	while (cmd[++i])
	{
		comands[i].args = cmd[i];
		printf("%s\n", comands[i].args);
	}
}
