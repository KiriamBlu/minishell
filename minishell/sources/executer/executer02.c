/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:05:21 by jporta            #+#    #+#             */
/*   Updated: 2022/04/27 02:36:08 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	finish(int fd1, int fd0, int pid)
{
	static int	status;

	close(fd1);
	dup2(fd0, STDIN_FILENO);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == EXIT_FAILURE)
		exit(1);
}

void	simba(t_minib *minilst, int i, int k)
{
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_errorpipex(0);
	pid = fork();
	if (pid == -1)
		ft_errorpipex(0);
	if (pid == 0)
	{
		if (minilst->cmds[i].in_fd != STDIN_FILENO)
		{
			dup2(minilst->cmds[i].in_fd, STDIN_FILENO);
			close(minilst->cmds[i].in_fd);
		}
		if (fd[1] != STDOUT_FILENO)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		printf("out %d\n", fd[1]);
		printf("in %d\n", fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ejecucion(minilst, i, k);
		minilst->cmds[i].in_fd = fd[0];
	}
	else
		finish(fd[1], fd[0], pid);
}
