/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:16:17 by jporta            #+#    #+#             */
/*   Updated: 2022/02/21 19:16:00 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoinmod(char *line, char c)
{
	char	*tmp;
	int		i = 0;
	int		j = 0;

	if (!line)
	{
		tmp = (char *)malloc(2);
		tmp[0] = c;
		tmp[1] = 0;
	}
	else
	{
		while (line[i])
			i++;
		tmp = (char *)malloc(i + 2);
		while (j < i)
		{
			tmp[j] = line[j];
			j++;
		}
		tmp[j] = c;
		tmp[j + 1] = 0;
		free(line);
	}
	return (tmp);
}

char	*ft_expenv(t_list *list, char *line)
{
	int		i;
	char	*arg;

	i = -1;
	arg = malloc(sizeof(char *));
	arg = NULL;
	while (line[++i])
	{
		if (line[i] == '\'')
			while (line[++i] != '\'')
				;
		else if (line[i] == '"')
		{
			while (line[++i] != '"')
			{
				if (line[i] == '$')
				{
					arg = ft_strjoinmod(arg, line[i]);
					while (ft_isalnum(line[++i]) != 0 || line[i] == '$')
						arg = ft_strjoinmod(arg, line[i]);
				}
			}
		}
		if (line[i] == '$')
		{
			arg = ft_strjoinmod(arg, line[i]);
			while (ft_isalnum(line[++i]) != 0 || line[i] == '$')
				arg = ft_strjoinmod(arg, line[i]);
		}
	}
	return (arg);
}

char	*ft_position(t_list *list, char *aux)
{
	int		i;
	char	*tmp;

	i = 0;
	i = getposinlst(list, aux);
	printf("%d\n", i);
	tmp = ft_calloc(sizeof(char), 1);
	if (i < 0)
		return (tmp);
	tmp = getlineinenv(list, i);
	return (tmp);
}

char	**ft_expandenv(char **aux, t_list *list)
{
	int		i;
	char	**expand;
	int		a;
	char	*temp;

	i = -1;
	a = 0;
	while (aux[++i])
		a++;
	i = -1;
	expand = ft_calloc(sizeof(char *), a);
	while (aux[++i])
	{
		temp = ft_calloc(sizeof(char), 1);
		temp = ft_position(list, aux[i]);
		expand[i] = ft_strdup(temp);
		free(temp);
	}
	i = -1;
	while (expand[++i])
		printf("%s\n", expand[i]);
	freemat(aux);
	return (expand);
}

char	*ft_newline(char *line, char **aux)
{
	int		i;
	char	*newline;
	int		a;
	int		j;

	newline = ft_calloc(sizeof(char *), 17);
	i = -1;
	a = 0;
	j = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			newline = ft_strjoinmod(newline, line[i]);
			while (line[++i] != '\'')
				newline = ft_strjoinmod(newline, line[i]);
			newline = ft_strjoinmod(newline, line[i]);
		}
		if (line[i] == '"')
		{
			while (line[++i] != '"')
			{
				if (line[i] == '$')
				{
					while (aux[a][++j] != '=')
						i++;
					while (aux[a][++j])
						newline = ft_strjoinmod(newline, aux[a][j]);
					j = 0;
					a++;
				}
				newline = ft_strjoinmod(newline, line[i]);
			}
			i++;
		}
		if (line[i] == '$')
		{
			while (aux[a][++j] != '=')
				i++;
			while (aux[a][++j])
				newline = ft_strjoinmod(newline, aux[a][j]);
				j = 0;
				a++;
		}
		newline = ft_strjoinmod(newline, line[i]);
	}
	printf("%s\n", newline);
	return (newline);
}

char	**lexer(t_list *list, char *line)
{
	char	**aux;
	char	*dollar;
	int		i;
	char	*newline;

	dollar = ft_expenv(list, line);
	if (!dollar)
	{
		aux = ft_prepare(line);
		return (aux);
	}
	aux = NULL;
	aux = ft_split(dollar, '$');
	aux = ft_expandenv(aux, list);
	i = -1;
	newline = ft_calloc(sizeof(char *), 17);
	newline = ft_newline(line, aux);
	while (aux[++i])
		printf("%s\n", aux[i]);
	//aux = ft_prepare(expand);
	return (0);
}
