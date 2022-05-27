/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:27 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/25 14:39:22 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_getlenname(char *line, int start)
{
	int	i;

	i = start + 1;
	while (ft_isalnum(line[i]) == 1 && line[i + 1] != ' '
		&& line[i + 1] != '$' && line[i + 1] != '"' && line[i + 1] != '\''
		&& line[i + 1] != '|')
		i++;
	return (i - start);
}

char	*expanddollar(char *name, t_minib *minilst)
{
	char	*expand;
	int		check;

	if (name[0] == '?')
		return (ft_itoa(minilst->cmdstatus));
	check = getposinlst(minilst->envp, name) + 1;
	if (check == 0)
	{
		expand = ft_strdup("");
		return (expand);
	}
	expand = getlineinenv(minilst->envp, check);
	return (ft_substr(expand, ft_strlen(name) + 1, ft_strlen(expand)));
}

int	get_len(char *line, int a)
{
	int	j;
	int	flag;

	j = a;
	flag = 0;
	if (line[0] == '$')
		return (0);
	while (line[j] != '$')
	{
		if (line[j] == '\'' && flag == 1)
			while (line[++j] != '\'')
				;
		if (line[a] == '"')
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		j++;
	}
	return (j);
}
