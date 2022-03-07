/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:27 by jporta            #+#    #+#             */
/*   Updated: 2022/03/02 03:06:49 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int countdollars(char *line)
{
	int a;
	int k;

	a = 0;
	k = 0;
	while (line[a])
	{
		if(line[a] == '\'')
			while(line[++a] != '\'')
				;
		else if (line[a] == '$')
			k++;
		a++;
	}
	return (k);
}

 int len_expan (char *str)
 {
	 int i = 1;
	 while (str[i])
	 {
		 if (str[i] == ' ' || str[i] == '$' || str[i] == '"')
		 	break;
		 i++;
	 }

	 return (i);
	 
 }

int ft_getlenname(char *line, int start)//mirar si start es == a dollar o el anterior
{
	int i;

	i = start + 1;
	if(line[i] == '?')
		return(2);
	while(ft_isalnum(line[i]) == 1 && line[i] != ' ' && line[i] != '$' && line[i] != '"')
		i++;
	return(i - start);
}

char *expanddollar(char *line, int start, t_list *list)
{
	char	*name;
	char	*expand;
	int		check;

	name = ft_substr(line, start + 1, ft_getlenname(line, start));
	if(name[0] == '?')
	{
		free(name);
		return("$");
	}
	check = getposinlst(list, name) + 1;
	free(name);
	if(check == -1)
	{
		free(name);
		return(" ");
	}
	expand = getlineinenv(list, check);
	return(ft_substr(expand, ft_getlenname(line, start), ft_strlen(expand)));
}

char *ft_prueba(char *line, t_list *list)
{
	int	i;
	int	a;
	int k;
	char *full;
	char *tmp;
	char *aux;
	
	i = 0;
	a = 0;
	k = countdollars(line);
	if(k == 0)
		return(ft_strdup(line));
	tmp = ft_strdup(line);
	full = ft_calloc(sizeof(char), 1);
	while (k > 0)
	{
		while (line[a] != '$')
		{
			if(line[a] == '\'')
				while(line[++a] != '\'')
					;
			a++;
		}
		aux = ft_substr(line, i, a);
		aux = ft_strjoin(aux, expanddollar(line, a, list));
		full = ft_strjoin(full, aux);
		free(aux);
		a += ft_getlenname(line, a);
		free(tmp);
		tmp = ft_substr(line, a, full - line);
		i = a;
		k--;
	}

	full = ft_strjoin(full, tmp);
	
	return (full);
}
