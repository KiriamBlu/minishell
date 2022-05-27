/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:27 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/27 21:49:34 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipesin(char *expanded)
{
	int	i;

	i = ft_strlen(expanded);
	while (expanded[i] == ' ' && expanded[i])
		i--;
	if (expanded[i] == '|')
		return (0);
	else
		return (1);
}

int	helpecho(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == ' ')
			break ;
		if (line[i] == '\'')
			while (line[++i] != '\'')
				;
		if (line[i] == '"')
			while (line[++i] != '"')
				;
		i++;
	}
	return (i);
}

int	checkarg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] == ' ' && arg[i])
		i++;
	if (arg[i] == '>' || arg[i] == '\0')
		return (1);
	else
		return (2);
	return (1);
}
