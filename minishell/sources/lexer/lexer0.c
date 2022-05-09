/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:05:21 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/05 18:53:48 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		countpipe(char *expanded);
int		plus(char *expanded, int i);

char	**lexer(char *expanded)
{
	int		i;
	int		a;
	int		numcom;
	int		status;
	char	**comands;

	numcom = countpipe(expanded);
	comands = malloc(sizeof(char *) * numcom + 1);
	i = 0;
	a = 0;
	status = 0;
	while (numcom > 0)
	{
		i = plus(expanded, i);
		comands[status] = ft_substr(expanded, a, i - a);
		i += 1;
		a = i;
		status++;
		numcom--;
	}
	comands[status] = 0;
	return (comands);
}

int	morfeo(t_cmds *com, char **line)
{
	int		i[2];
	char	**aux;
	char	*tmp;

	i[0] = 0;
	while (line[i[0]])
	{
		i[1] = 0;
		tmp = checkredirect(line[i[0]], &com[i[0]].filein, &com[i[0]].fileout);
		if (tmp == NULL)
			return (-1);
		aux = ft_split(tmp, ' ');
		if (aux[0])
		{
			com[i[0]].cmd = ft_strdup(aux[0]);
			freemat(aux);
			while (tmp[i[1]++] == ' ')
				;
			i[1] += ft_strlen(com[i[0]].cmd);
			com[i[0]].args = ft_substr(tmp, i[1], ft_strlen(tmp));
		}
		free(tmp);
		i[0]++;
	}
	return (0);
}

int	plus(char *expanded, int i)
{
	while (expanded[i] != '|' && expanded[i])
	{
		if (expanded[i] == '\'')
			while (expanded[++i] != '\'')
				;
		if (expanded[i] == '"')
			while (expanded[++i] != '"')
				;
		i++;
	}
	return (i);
}

char	**ft_prepare(char *line)
{
	char	**cmd;

	if (count_c(line, '|') > 0)
	{
		cmd = ft_splitmod(line, '|');
		return (cmd);
	}
	else
	{
		cmd = malloc(sizeof(char **) * 1);
		cmd[0] = ft_strdup(line);
	}
	cmd[1] = NULL;
	return (cmd);
}

int	countpipe(char *expanded)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (expanded[i])
	{
		if (expanded[i] == '|')
			k++;
		if (expanded[i] == '\'')
			while (expanded[++i] != '\'')
				;
		if (expanded[i] == '"')
			while (expanded[++i] != '"')
				;
		i++;
	}
	return (k + 1);
}
