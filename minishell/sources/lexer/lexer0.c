/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:05:21 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/25 16:56:30 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		countpipe(char *expanded);
int		plus(char *expanded, int i);
char	*ft_prepare(char *line);

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
	char	*aux;
	char	*tmp;

	i[0] = 0;
	while (line[i[0]])
	{
		i[1] = 0;
		tmp = checkredirect(line[i[0]], &com[i[0]].filein, &com[i[0]].fileout);
		if (tmp == NULL)
			return (-1);
		aux = ft_prepare(tmp);
		if (aux)
		{
			com[i[0]].cmd = comparse(aux);
			while (tmp[i[1]++] == ' ')
				;
			i[1] += ft_strlen(aux);
			com[i[0]].args = ft_substr(tmp, i[1], ft_strlen(tmp));
			free(aux);
			free(tmp);
		}
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

char	*ft_prepare(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] == ' ' && line[i])
		i++;
	if (i == (int)ft_strlen(line))
		return (NULL);
	j = i;
	while (line[j] != ' ' && line[j])
	{
		if (line[j] == '"')
			while (line[++j] != '"' && line[j])
				;
		if (line[j] == '\'')
			while (line[++j] != '\'' && line[j])
				;
		j++;
	}
	return (ft_substr(line, i, j - i));
}

int	countpipe(char *expanded)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (ft_comprobapipe(expanded) == 0)
		ft_errorpipex(1);
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
