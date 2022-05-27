/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/23 19:41:31 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	auxcount(char *print, int j, int *l)
{
	int	i;

	i = j + 1;
	if (print[i] == '-')
		return (j - 1);
	while (print[i])
	{
		if (print[i] == 'n')
			i++;
		else
			break ;
	}
	if (print[i] == ' ' || print[i] == '\0')
	{
		*l = 1;
		j = i;
	}
	else
		j--;
	return (j);
}

int	start(char *print, int *l)
{
	int	j;
	int	i;

	j = 0;
	while (print[j])
	{
		if (print[j] == '-')
		{
			i = auxcount(print, j, l);
			if (print[i] != ' ' || i == j - 1)
				return (j);
			else
				j = i;
			if (print[i] == '\0' || print[i] == '-')
				return (j);
		}
		else if (print[j] == ' ')
			j++;
		else
			break ;
	}
	return (j);
}

char	**argsprepecho(char *print)
{
	int		i;
	int		a;
	int		status;	
	int		numcom;
	char	**aux;

	aux = ft_calloc(sizeof(char *), count_c(print, ' ') + 1);
	i = 0;
	a = 0;
	status = 0;
	numcom = count_c(print, ' ');
	while (numcom > 0)
	{
		i = helpecho(print, i);
		aux[status] = ft_substr(print, a, i - a);
		while (print[i] == ' ')
			i += 1;
		a = i;
		status++;
		numcom--;
	}
	return (aux);
}

void	printecho(char **aux, int fileout, int l)
{
	char	*str;

	str = comparse(aux[l]);
	ft_putstr_fd(str, fileout);
	if (aux[l + 1] != (void *)0)
			ft_putstr_fd(" ", fileout);
	free(str);
}

int	checkforecho(char *cmd, char *arg, int fileout, int *status)
{
	int		i;
	int		j;
	int		l;
	char	*print;
	char	**aux;

	if (!cmd || ft_strcmp(cmd, "echo") != 0)
		return (0);
	i = 0;
	l = -1;
	j = start(arg, &i);
	print = ft_substr(arg, j, ft_strlen(arg));
	aux = argsprepecho(print);
	free(print);
	while (aux[++l])
		printecho(aux, fileout, l);
	if (i != 1)
		ft_putchar_fd('\n', fileout);
	*status = 0;
	freemat(aux);
	return (1);
}
