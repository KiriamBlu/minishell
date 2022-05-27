/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:27 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/25 15:01:59 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
