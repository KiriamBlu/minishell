/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:31:10 by jporta            #+#    #+#             */
/*   Updated: 2022/04/19 22:05:32 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		printf("mal");
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

void executer(t_minib *minilst, int i)
{
	char **envp;
	char *arto;
	char *paths;
	char **pths2;
	int pid;
	static int	status;

	pid = fork();
	if (pid == 0)
	{
		envp = createlstarray(minilst->envp, ft_lstsize(minilst->envp)); //REPLICA ENV
		arto = ft_strjoin(minilst->cmds[i].cmd, " "); //UNION COMANDO
		arto = ft_strjoin(arto, minilst->cmds[0].args); // UNION COMANDO CON ARGUMENTO
		paths = path(minilst->cmds[i].cmd, envp); // BUSCA PATH
		pths2 = ft_split(arto, ' '); //SPLITE PATH
		if (execve(paths, pths2, envp) == -1) //EXCUVE
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			printf("mal\n");
		}
	}
	waitpid(pid, &status, 0);
}