/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:56:20 by jporta            #+#    #+#             */
/*   Updated: 2022/02/23 20:38:59 by jporta           ###   ########.fr       */
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

//"hola" "|" | pepe "|"