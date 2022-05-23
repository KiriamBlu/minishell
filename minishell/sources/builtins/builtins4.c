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

int	checkforecho(char *cmd, char *arg, int fileout, int *status)
{
	int		i;
	int		j;
	char	*print;

	if (ft_strcmp(cmd, "echo") != 0)
		return (0);
	print = comparse(arg);
	j = -1;
	i = 0;
	while (print[++j] == ' ')
		;
	while (print[j])
	{
		if (print[j] == '-' && print[j + 1] == 'n' && print[j + 2] == ' ')
		{
			j += 2;
			while (print[j] == ' ')
				j++;
			i = 1;
		}
		j = printarg(print, j, fileout);
	}
	if (i != 1)
		ft_putchar_fd('\n', fileout);
	return (returnstatusfree(print, status));
}
