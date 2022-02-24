/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:16:17 by jporta            #+#    #+#             */
/*   Updated: 2022/02/23 20:33:20 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoinmod(char *line, char c)
{
	char	*tmp;
	int		i = 0;
	int		j = 0;


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
	return (tmp);
}

char	*ft_expenv(t_list *list, char *line)
{
	int		i;
	char	*arg;

	i = -1;
	arg = malloc(sizeof(char *));
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
	if (arg[0] == '\0')
	{
		free(arg);
		arg = NULL;	
	}
	return (arg);
}

char	*ft_position(t_list *list, char *aux)
{
	int		i;
	char	*tmp;

	i = 0;
	i = getposinlst(list, aux);
	tmp = ft_strdup(" ");
	if (i < 0)
		return (tmp);
	free(tmp);
	tmp = ft_strdup(getlineinenv(list, i + 1));
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
		temp = ft_position(list, aux[i]);
		expand[i] = ft_strdup(temp);
		//free(temp);
	}
	return (expand);
}

char	*ft_newline(char *line, char **aux)
{
	int		i;
	char	*newline;
	int		a;
	int		j;

	newline = ft_calloc(sizeof(char *), 1);
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
		else if (line[i] == '"')
		{
			while (line[++i] != '"')
			{
				if (line[i] == '$' && line[i + 1])
				{
					while (aux[a][++j] != '=' && line[i] != '\0')
						i++;
					while (aux[a][++j])
						newline = ft_strjoinmod(newline, aux[a][j]);
					if (a > 0)
						i++;
					j = 0;
					a++;
				}
				else
					newline = ft_strjoinmod(newline, line[i]);
			}
		}
		else if (line[i] == '$')
		{
			while (aux[a][++j] != '=' && line[i] != '\0')
				i++;
			while (aux[a][++j])
			{
				newline = ft_strjoinmod(newline, aux[a][j]);
				printf("este: %s\n", newline);
			}
			if (a > 0)
				i++;
			j = 0;
			a++;
		}
		else
			newline = ft_strjoinmod(newline, line[i]);
	}
	return (newline);
}

char	**lexer(t_list *list, char *line)
{
	char	**aux;
	char	*dollar;
	char	*newline;
	char	**tmp;

	dollar = ft_expenv(list, line);
	if (!dollar || ft_strlen(dollar) == 1)
	{
		aux = ft_prepare(line);
		return (aux);
	}
	printf(" este%s\n", dollar);
	aux = ft_split(dollar, '$');
	tmp = ft_expandenv(aux, list);
	freemat(aux);
	newline = ft_newline(line, tmp);
	printf("%s\n", newline);
	tmp = ft_prepare(newline);
	printf("tmp: %s\n%s\n", tmp[0], tmp[1]);
	return (tmp);
}

//hola