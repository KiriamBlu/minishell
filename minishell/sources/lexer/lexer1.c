/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:27 by jporta            #+#    #+#             */
/*   Updated: 2022/04/19 23:17:42 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int countdollars(char *line)
{
	int a;
	int k;
	int flag;

	a = 0;
	k = 0;
	flag = 0;
	while (line[a])
	{
		if(line[a] == '\'' && flag == 0)
			while(line[++a] != '\'')
				;
		if(line[a] == '"')
		{
			if(flag == 0)
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
	while(ft_isalnum(line[i]) == 1 && line[i + 1] != ' ' && line[i + 1] != '$' && line[i + 1] != '"' && line[i + 1] != '\'')
		i++;
	return(i - start);
}

char *expanddollar(char *name, t_minib *minilst)
{
	char	*expand;
	int		check;

	if(name[0] == '?')
		return(ft_itoa(minilst->cmdstatus));
	check = getposinlst(minilst->envp, name) + 1;
	if(check == 0)
	{
		expand = ft_strdup(" ");
		return(expand);
	}
	expand = getlineinenv(minilst->envp, check);
	return(ft_substr(expand, ft_strlen(name) + 1, ft_strlen(expand)));
}

int get_len(char *line, int a)
{
	int j;
	int flag;

	j = a;
	flag = 0;
	if(line[0] == '$')
		return(0);
	while (line[j] != '$')
	{
		if(line[j] == '\'' && flag == 1)
			while(line[++j] != '\'')
				;
		if(line[a] == '"')
		{
			if(flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		j++;
	}
	return(j);
}

char *finished(char *line, char *longstr, int a)
{
	char *full;
	char *aux;

	if (ft_strlen(longstr) > ft_strlen(line))
		full = ft_substr(line, a, (ft_strlen(longstr) - ft_strlen(line)));
	else
		full = ft_substr(line, a, (ft_strlen(line) - ft_strlen(longstr)));
	aux = freezerjoin(longstr, full);
	return(aux);
}

char *expander(char *line, t_minib *minilst)
{
	int	i;
	int	a;
	int k;
	char *longstr;
	char *tmp;
	char *aux;
	char *last;
	
	i = 0;
	a = 1;
	k = countdollars(line);
	longstr = NULL;
	if(k == 0)
		return(ft_strdup(line));
	while (k > 0)
	{
		a = get_len(line, a);
		aux = ft_substr(line, i, a - i);
		tmp = ft_substr(line, a + 1, ft_getlenname(line, a));
		if(tmp[0] != '?')
			a += 1;
		a += ft_strlen(tmp);
		last = freezerjoin(aux, expanddollar(tmp, minilst));
		free(tmp);
		longstr = freezerjoin(longstr, last);
		i = a;
		k--;
	}
	return (finished(line, longstr, a));
}
