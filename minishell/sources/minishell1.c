/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:18:50 by jporta            #+#    #+#             */
/*   Updated: 2022/05/27 21:15:53 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins(t_minib *minilst, int k, int i)
{
	k += checkforexit(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
	k += checkforcd(minilst->cmds[i].cmd,
			minilst->cmds[i].args, minilst, minilst->cmds[i].fileout);
	k += checkforenv(minilst->cmds[i].cmd,
			minilst->envp, minilst->cmds[i].fileout, &minilst->cmdstatus);
	k += checkforecho(minilst->cmds[i].cmd,
			minilst->cmds[i].args, minilst->cmds[i].fileout,
			&minilst->cmdstatus);
	if ((minilst->cmds[i].cmd && ft_strcmp(minilst->cmds[i].cmd, "pwd") == 0)
		|| (minilst->cmds[i].cmd
			&& ft_strcmp(minilst->cmds[i].cmd, "/bin/pwd") == 0))
	{
		free(minilst->pwd);
		minilst->pwd = getcwd(NULL, 0);
		ft_putstr_fd(minilst->pwd, minilst->cmds[i].fileout);
		ft_putchar_fd('\n', minilst->cmds[i].fileout);
		k += 1;
	}
	k += checkforexport(minilst->cmds[i].cmd, minilst->cmds[i].args,
			minilst, minilst->cmds[i].fileout);
	k += checkforunset(minilst->cmds[i].cmd, minilst->cmds[i].args,
			minilst);
	return (k);
}

void	ejecucion(t_minib *minilst, int i, int num, int flag)
{
	int		k;
	char	*aux;

	aux = ft_strjoin("_=", minilst->cmds[i].cmd);
	k = getposinlst(minilst->envp, "_");
	if (k != -1)
	{
		delpos(&minilst->envp, k);
		putinpos(&minilst->envp, k, aux);
	}
	else
		putinpos(&minilst->envp, 0, aux);
	k = 0;
	k += builtins(minilst, k, i);
	if (minilst->cmds[i].cmd && k == 0)
		executer(minilst, i, num);
	else if (flag == 1)
		exit(0);
}
