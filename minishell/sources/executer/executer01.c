/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:31:10 by jporta            #+#    #+#             */
/*   Updated: 2022/05/30 17:45:54 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_errorpipex(int index)
{
	if (index == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		ft_putstr_fd("Escromito: command not found\n", 2);
		exit(1);
	}
	else if (index == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		ft_putstr_fd("Escromito: command not found\n", 2);
	}
}

char	*path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);	
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

void	freezes_vr(char **pths2, char **envp, char **vars)
{
	freemat(pths2);
	freemat(envp);
	free(vars[0]);
	free(*vars);
}

void	executioner(char **pths2, char *cmd, char **vars, char **envp)
{
	if (pths2[0][0] == '/' || pths2[0][0] == '~' || pths2[0][0] == '.' ||
		access(pths2[0], X_OK) == 0)
	{
		if (execve(cmd, pths2, envp) == -1)
			ft_errorpipex(0);
	}
	else
	{
		vars[2] = path(cmd, envp);
		if (vars[2] == NULL)
			ft_errorpipex(0);
		else if (execve(vars[2], pths2, envp) == -1)
			ft_errorpipex(0);
		free(vars[2]);
	}
	freezes_vr(pths2, envp, vars);
}

void	executer(t_minib *minilst, int i, int num)
{
	char		**pths2;
	char		**envp;
	char		*vars[3];

	if (minilst->cmdnum == 1 || num == 1)
		minilst->cmds[i].pid = fork();
	else
		minilst->cmds[i].pid = 0;
	if (minilst->cmds[i].pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		envp = createlstarray(minilst->envp, ft_lstsize(minilst->envp));
		vars[0] = ft_strjoin(minilst->cmds[i].cmd, " ");
		vars[1] = comparse(minilst->cmds[i].args);
		vars[0] = ft_strjoin(vars[0], vars[1]);
		free(vars[1]);
		pths2 = ft_split(vars[0], ' ');
		executioner(pths2, minilst->cmds[i].cmd, vars, envp);
		freezes_vr(pths2, envp, vars);
	}
	if (minilst->cmdnum == 1 || num == 1)
		waitpid(minilst->cmds[i].pid, &(minilst->cmdstatus), 0);
	if (WIFSIGNALED(minilst->cmdstatus))
		minilst->cmdstatus = 127;
}
