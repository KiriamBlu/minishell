/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:18:54 by jporta            #+#    #+#             */
/*   Updated: 2022/06/01 22:33:15 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process(t_minib *minilst, int i)
{
	int	status;

	if (minilst->cmdnum > 1)
	{
		while (i < minilst->cmdnum)
			simba(minilst, i++);
		i = -1;
		while (++i < minilst->cmdnum)
		{
			waitpid(minilst->cmds[i].pid, &status, 0);
			statuschecker(status);
		}
	}
	else
	{
		dup2(minilst->cmds[i].filein, STDIN_FILENO);
		dup2(minilst->cmds[i].fileout, STDOUT_FILENO);
		ejecucion(minilst, i, 1, 0);
	}
	return (i);
}

void	checkeverything(char *line, t_minib *minilst)
{
	int	i;
	int	files[4];

	i = -1;
	if (prepline(line, minilst) == -1)
		return ;
	if (checkinout(minilst) == -1)
		return ;
	files[2] = dup(STDOUT_FILENO);
	files[3] = files[2];
	files[0] = dup(STDIN_FILENO);
	files[1] = files[0];
	while (++i < minilst->cmdnum)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		i += process(minilst, i);
		dup2(files[0], STDIN_FILENO);
		close(files[0]);
		dup2(files[2], STDOUT_FILENO);
		close(files[2]);
	}
}
