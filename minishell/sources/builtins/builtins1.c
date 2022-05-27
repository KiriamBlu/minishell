/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/23 19:37:32 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	checkforenv(char *cmd, t_list *envp, int fileout, int *status)
{
	if ((cmd && ft_strcmp("env", cmd) == 0)
		|| (cmd && ft_strcmp("/usr/bin/env", cmd) == 0))
	{
		printlist(envp, fileout);
		*status = 0;
		return (1);
	}
	return (0);
}

int checkforexit(char *cmd, char *arg, t_minib *minilst)
{
	int		i;
	char	**aux;
	char	*tmp;

	i = 0;
	if (cmd && ft_strcmp(cmd, "exit") == 0)
	{
		aux = ft_split(arg, ' ');
		printf("exit\n");
		if (!aux[0])
		{
			freemat(aux);
			freeeverything(minilst);
			free(minilst->promt);
			exit(0);
		}
		tmp = comparse(aux[0]);
		if (aux[1])
		{
			errorprintf("minishell: exit: too many arguments\n", &minilst->cmdstatus);
			minilst->cmdstatus = 255;
			freemat(aux);
			free(tmp);
			return (1);
		}
		i = -1;
		while (tmp[++i])
		{
			if (ft_isdigit(tmp[i]) != 1)
			{
				printf("minishell: exit: %s: numeric argument required\n", aux[0]);
				minilst->cmdstatus = 255;
				free(tmp);
				tmp = ft_strdup("255");
				break ;
			}
		}
		freeeverything(minilst);
		free(minilst->promt);
		freemat(aux);
		exit(ft_atoi(tmp));
	}
	return (0);
}