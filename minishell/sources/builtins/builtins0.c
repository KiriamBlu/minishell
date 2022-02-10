/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:20:03 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/10 20:19:08 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	checkforenv(char **line, t_list *envp)
{
	int i;

	i = -1;
	if (ft_strcmp(line[0], "env") == 3)
	{
		if(line[1])
			return ;
		printlist(envp);
	}
}

void	cd_update_env(int i[2], t_minib *minilst)
{
	char *tmp;
 
	delpos(minilst->envp, i[1]);
	putinpos(minilst->envp, i[1], ft_strjoin("OLDPWD=", getlineinenv(minilst->envp, i[0]) + 4));
	tmp = getcwd(NULL, 0);
	delpos(minilst->envp, i[0]);
	putinpos(minilst->envp, i[0], ft_strjoin("PWD=", tmp));
	free(tmp);
}

char	*check_pwd(char *str, int home, t_minib *minilst)
{
	char	*s;

	s = NULL;
	if (!str)
	{
		if (home != -1)
			s = ft_strdup(getlineinenv(minilst->envp, home) + 5);
		else
			printf("minishell: cd: HOME not set\n");
	}
	else
		s = ft_strdup(str);
	return (s);
}


void	checkforcd(char **line, t_minib *minilst)
{
	char	*str;
	int		i[2];

	if (ft_strcmp(line[0], "cd") != 2)
		return	;
	if (getposinlst(minilst->envp, "PWD") == -1)
	{
		minilst->pwd = getcwd(NULL, 0);
		putinpos(minilst->envp, 16, minilst->pwd);
	}
	i[0] = getposinlst(minilst->envp, "PWD");
	i[1] = getposinlst(minilst->envp, "OLDPWD");
	str = check_pwd(line[1], getposinlst(minilst->envp, "HOME"), minilst);
	if(chdir(str) == -1)
		minilst->pwd = getcwd(NULL, 0);
	cd_update_env(i, minilst);
	free(str);
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