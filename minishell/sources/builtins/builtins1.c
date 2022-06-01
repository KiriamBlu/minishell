/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/06/01 22:39:59 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	checkforenv(char *cmd, t_list *envp, int fileout)
{
	if ((cmd && ft_strcmp("env", cmd) == 0)
		|| (cmd && ft_strcmp("/usr/bin/env", cmd) == 0))
	{
		printlist(envp, fileout);
		g_cmd_status = 0;
		return (1);
	}
	return (0);
}

int	exitcheck(t_minib *minilst, char **aux, char *tmp)
{
	printf("exit\n");
	if (!aux[0])
	{
		freemat(aux);
		freeeverything(minilst);
		free(minilst->promt);
		free(tmp);
		exit(0);
	}
	if (aux[1])
	{
		errorprintf("Escromito: exit: too many arguments\n");
		g_cmd_status = 255;
		freemat(aux);
		return (1);
	}
	return (0);
}

void	freeexit(t_minib *minilst, char **aux, char *tmp)
{
	freeeverything(minilst);
	free(minilst->promt);
	freemat(aux);
	exit(ft_atoi(tmp));
}

int	checkforexit(char *cmd, char *arg, t_minib *minilst)
{
	int		i;
	char	**aux;
	char	*tmp;

	if (!cmd || ft_strcmp(cmd, "exit") != 0)
		return (0);
	tmp = comparse(arg);
	aux = ft_split(tmp, ' ');
	if (exitcheck(minilst, aux, tmp) == 1)
		return (1);
	i = -1;
	while (tmp[++i])
	{
		if (ft_isdigit(tmp[i]) != 1)
		{
			printf("Escromito: exit: %s: numeric argument required\n",
				aux[0]);
			g_cmd_status = 255;
			free(tmp);
			tmp = ft_strdup("255");
			break ;
		}
	}
	freeexit(minilst, aux, tmp);
	return (0);
}
