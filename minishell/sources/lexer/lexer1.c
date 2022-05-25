/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:27 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/25 14:37:24 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*finished(char *line, char *longstr, int a);
int		len_expan(char *str);
int		countdollars(char *line);
char	*initexpander(int *i, int *k, int *a, char *line);

char	*expander(char *line, t_minib *minilst, int i, int a)
{
	int		k;
	char	*longstr;
	char	*tmp;
	char	*aux;
	char	*last;

	longstr = initexpander(&i, &k, &a, line);
	if (k - 1 == 0)
		return (ft_strdup(line));
	while (--k > 0)
	{
		a = get_len(line, a);
		aux = ft_substr(line, i, a - i);
		tmp = ft_substr(line, a + 1, ft_getlenname(line, a));
		printf("este: %s\n", tmp);
		a += ft_strlen(tmp) + 1;
		if (tmp[0] == '?' && tmp[1] != ' ' && tmp[1] != '\0')
			a -= 1;
		last = freezerjoin(aux, expanddollar(tmp, minilst));
		free(tmp);
		longstr = freezerjoin(longstr, last);
		i = a;
	}
	return (finished(line, longstr, a));
}

char	*initexpander(int *i, int *k, int *a, char *line)
{
	*i = 0;
	*a = 1;
	*k = countdollars(line) + 1;
	return (NULL);
}

char	*finished(char *line, char *longstr, int a)
{
	char	*full;
	char	*aux;

	full = ft_substr(line, a, (ft_strlen(line)));
	aux = freezerjoin(longstr, full);
	free(line);
	return (aux);
}

int	countdollars(char *line)
{
	int	a;
	int	k;
	int	flag;

	a = 0;
	k = 0;
	flag = 0;
	while (line[a])
	{
		if (line[a] == '\'' && flag == 0)
			while (line[++a] != '\'')
				;
		if (line[a] == '"')
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		else if (line[a] == '$')
			k++;
		a++;
	}
	return (k);
}

int	len_expan(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '"')
			break ;
		i++;
	}
	return (i);
}
