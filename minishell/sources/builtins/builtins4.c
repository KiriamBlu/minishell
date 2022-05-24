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

int	start(char *print)
{
	int j;
	int i;

	j = ft_strlen(print);
	while (print[j])
	{
		if (print[j] == '"')
			while(print[j--] != '"' && print[j])
				;
		if (print[j] == '\'')
			while(print[j--] != '\'' && print[j])
				;
		if (print[j] == 'n' && print[j + 1] == ' ' &&
			(print[j - 1] == '-' || print[j - 1] == 'n'))
		{
			i = j;
			while (print[--i] != '-' && print[i])
				;
			if (print[i] == '-')
				break ;
		}	
		j--;
	}
	return(j);
}

int	checkforecho(char *cmd, char *arg, int fileout, int *status)
{
	int		i;
	int		j;
	char	*print;

	if (ft_strcmp(cmd, "echo") != 0)
		return (0);
	print = ft_strdup(arg);
	j = -1;
	i = 0;
	while (print[++j] == ' ')
		;
	while (print[j])
	{
		j += start(print);
		j = printarg(print, j, fileout);
	}
	if (i != 1)
		ft_putchar_fd('\n', fileout);
	return (returnstatusfree(print, status));
}
