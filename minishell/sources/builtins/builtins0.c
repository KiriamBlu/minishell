/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:20:03 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/09 01:52:02 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_update_env(int i[2], t_minib *minilst)
{
	char *tmp;

	tmp = getcwd(NULL, 0);
	minilst->envp[i[1]] = ft_strjoin("OLDPWD=", minilst->envp[i[0]] + 4);
	minilst->envp[i[0]]= ft_strjoin("PWD=", tmp);
}

char	*check_pwd(char *str, int oldpwd, int home, t_minib *minilst)
{
	char	*s;

	s = NULL;
	if (!ft_strncmp(str, "-", ft_maxlen(str, "-")))
	{
		if (oldpwd != -1)
			s = ft_strdup(minilst->envp[oldpwd] + 7);
		else
			printf("minishell: cd: OLDPWD not set\n");
	}
	else if (!str)
	{
		if (home != -1)
			s = ft_strdup(minilst->envp[home] + 5);
		else
			printf("minishell: cd: HOME not set\n");
	}
	else
		s = ft_strdup(str);
	return (s);
}


void	checkforcd(char **line, char **envp, t_minib *minilst)
{
	char	*str;
	int		i[2];

	if (ft_strcmp(line[0], "cd") != 2)
		return	;
	if (find_env("PWD", envp) == -1)
		minilst->pwd = getcwd(NULL, 0);
	i[0] = find_env("PWD", envp);
	i[1] = find_env("OLDPWD", envp);
	str = check_pwd(line[1], i[1], find_env("HOME", envp), minilst);
	//(check s)
	cd_update_env(i, minilst);
	free(str);
}

void	checkforenv(char **line, char **envp)
{
	int i;

	i = -1;
	if (ft_strcmp(line[0], "env") == 3)
	{
		if(line[1])
			return ;
		while(envp[++i])
			printf("%s\n", envp[i]);
	}
}

void checkforexit(char **line)
{
	int		i;

	i = 0;
	if (ft_strcmp(line[i], "exit") == 4)
	{
		printf("exit\n");
		if (!line[1])
			exit(0);
		if(line[2]) //SALIDA EN CASO DE MAS DE DOS ARGS
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
		i = -1;
		while(line[1][++i])
		{
			if(ft_isdigit(line[1][i]) != 1)
			{
				printf("minishell: exit: %s: numeric argument required\n", line[1]);
				break ;
			}
		}
		exit(ft_atoi(line[1]));
	}
}