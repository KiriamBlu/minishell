/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:05:21 by jporta            #+#    #+#             */
/*   Updated: 2022/05/27 17:47:56 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setout(t_minib *minilst, int i, int w)
{
	if (w == 0)
	{
		dup2(minilst->cmds[i].fileout, STDOUT_FILENO);
		dup2(minilst->cmds[i].filein, STDIN_FILENO);
	}
	if (w == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	simba(t_minib *minilst, int i)
{
	if (pipe (minilst->cmds[i].fd) == -1)
		ft_errorpipex(0);
	minilst->cmds[i].pid = fork();
	if (minilst->cmds[i].pid == -1)
		ft_errorpipex(0);
	if (minilst->cmds[i].pid == 0)
	{
		setout(minilst, i, 1);
		if (i == minilst->cmdnum - 1
			|| minilst->cmds[i].fileout != STDOUT_FILENO
			|| minilst->cmds[i].filein != STDIN_FILENO)
			setout(minilst, i, 0);
		else
		{
			close(minilst->cmds[i].fd[0]);
			dup2(minilst->cmds[i].fd[1], STDOUT_FILENO);
		}
		ejecucion(minilst, i, 0, 1);
	}
	else
	{
		close(minilst->cmds[i].fd[1]);
		dup2(minilst->cmds[i].fd[0], STDIN_FILENO);
		close(minilst->cmds[i].fd[0]);
	}
}
