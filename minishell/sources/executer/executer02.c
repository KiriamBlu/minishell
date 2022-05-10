/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:05:21 by jporta            #+#    #+#             */
/*   Updated: 2022/05/09 20:48:53 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	finish(int fd1, int fd0, int pid)
{
	static int	status;

	close(fd1);
	dup2(fd0, STDIN_FILENO);
	waitpid(pid, &status, 0);
	close(fd0);
}

void	simba(t_minib *minilst, int i)
{
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1 )
		ft_errorpipex(0);
	pid = fork();
	if (pid == -1)
		ft_errorpipex(0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ejecucion(minilst, i, 0, 1);
	}
	else
		finish(fd[1], fd[0], pid);
}
