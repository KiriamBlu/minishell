/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:05:21 by jporta            #+#    #+#             */
/*   Updated: 2022/04/29 00:14:45 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	simba(t_minib *minilst, int i, int k)
// {
// 	int		pid;
// 	int		fd[2];
// 	int		status;
// 	int		w;

// 	if (pipe(fd) == -1)
// 		ft_errorpipex(0);
// 	pid = fork();
// 	if (pid == -1)
// 		ft_errorpipex(0);
// 	if (pid == 0)
// 	{
// 		if (i == 0)//primero
// 		{
// 			dup2(fd[0], STDOUT_FILENO);
// 			minilst->cmds[i + 1].filein = fd[1];	
// 			ejecucion(minilst, i, k, 0);
// 		}
// 		else if (i < minilst->cmdnum - 1)//en medio
// 		{
// 			dup2(fd[0], STDOUT_FILENO);
// 			minilst->cmds[i + 1].filein = fd[1];
// 			dup2(minilst->cmds[i].filein, STDIN_FILENO);
// 			ejecucion(minilst, i, k, 0);
// 		}
// 		else if (i == minilst->cmdnum - 1)//ultimo
// 		{
// 			dup2(minilst->cmds[i].filein, STDIN_FILENO);
// 			dup2(minilst->cmds[1].fileout , STDOUT_FILENO);
// 			ejecucion(minilst, i, k, 0);
// 		}
// 	}
// 	else
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		waitpid(pid, &status, 0);
// 		w = -1;
// 		while (++w < minilst->cmdnum && i == minilst->cmdnum - 1)
// 		{
// 			close(fd[0]);
// 			close(fd[1]);
// 		}
// 	}
// }

void	finish(int fd1, int fd0, int pid)
{
	static int	status;

	close(fd1);
	dup2(fd0, STDIN_FILENO);
	waitpid(pid, &status, 0);
}

void	simba(t_minib *minilst, int i)
{
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_errorpipex(0, &minilst->cmdstatus);
	pid = fork();
	if (pid == -1)
		ft_errorpipex(0, &minilst->cmdstatus);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ejecucion(minilst, i, 0);
	}
	else
		finish(fd[1], fd[0], pid);
}
