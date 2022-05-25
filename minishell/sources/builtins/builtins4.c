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

int	printarg(char *print, int j, int fileout)
{
	int	i;

	i = j;
	if (print[i] == '"' || print[i] == '\'')
	{
		if (print[i] == '"')
		{
			while (print[++i] != '"')
				ft_putchar_fd(print[i], fileout);
		}
		else if (print[i] == '\'')
		{
			while (print[++i] != '\'')
				ft_putchar_fd(print[i], fileout);
		}
	}
	else
		ft_putchar_fd(print[i], fileout);
	i++;
	return (i);
}

int	returnstatusfree(char *print, int *status)
{
	free(print);
	*status = 0;
	return (1);
}

int auxcount(char *print, int j, int *l)
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
			break;
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
			break;
	}
	return (j);
}

int	checkforecho(char *cmd, char *arg, int fileout, int *status)
{
	int		i;
	int		j;
	char	*print;

	if (ft_strcmp(cmd, "echo") != 0)
		return (0);
	print = ft_strdup(arg);
	i = 0;
	j = start(print, &i);
	while (print[j])
		j = printarg(print, j, fileout);
	if (i != 1)
		ft_putchar_fd('\n', fileout);
	return (returnstatusfree(print, status));
}
