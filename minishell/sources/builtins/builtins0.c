/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/23 19:38:25 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*c_pwd(char *str, int home, t_minib *minilst, int fileout);
void	updateenv(t_minib *minilst);
void	cd_update_env(t_minib *minilst);

int	checkforcd(char *cmd, char *arg, t_minib *minilst, int fileout)
{
	char	*str;
	char	**args;

	if (!cmd || ft_strcmp("cd", cmd) != 0)
		return (0);
	args = ft_split(arg, ' ');
	str = c_pwd(args[0], getposinlst(minilst->envp, "HOME"), minilst, fileout);
	if (chdir(str) == -1)
	{
		if (!minilst->pwd)
			minilst->pwd = getcwd(NULL, 0);
		if (str)
		{
			minilst->cmdstatus = 1;
			printf("minishell: cd: %s: No such file or directory\n", str);
		}
	}
	else
	{
		cd_update_env(minilst);
		minilst->cmdstatus = 0;
	}
	freemat(args);
	free(str);
	return (1);
}

void	updateenv(t_minib *minilst)
{
	char	*tmp;
	int		i;
	int		j;

	i = getposinlst(minilst->envp, "OLDPWD");
	j = getposinlst(minilst->envp, "PWD");
	if (i != -1 && j != -1)
	{
		delpos(&minilst->envp, i);
		putinpos(&minilst->envp, i, ft_strjoin("OLDPWD=",
				getlineinenv(minilst->envp, (j + 1)) + 4));
	}
	if (j != -1)
	{
		tmp = getcwd(NULL, 0);
		delpos(&minilst->envp, j);
		putinpos(&minilst->envp, j, ft_strjoin("PWD=", tmp));
		free(tmp);
	}
}

void	cd_update_env(t_minib *minilst)
{
	char	*tmp;
	int		i;
	int		j;

	updateenv(minilst);
	j = getposinlst(minilst->exp, "PWD");
	i = getposinlst(minilst->exp, "OLDPWD");
	if (i != -1 && j != -1)
	{
		delpos(&minilst->exp, i);
		putinpos(&minilst->exp, i, ft_strjoin("OLDPWD=",
				getlineinenv(minilst->exp, j) + 4));
	}
	if (j != -1)
	{
		tmp = getcwd(NULL, 0);
		delpos(&minilst->exp, j);
		putinpos(&minilst->exp, j, ft_strjoin("PWD=", tmp));
		free(tmp);
	}
}

char	*c_pwd(char *str, int home, t_minib *minilst, int fileout)
{
	char	*s;
	int		i;

	s = NULL;
	if (!str)
	{
		if (home != -1)
			s = ft_strdup(getlineinenv(minilst->envp, home + 1) + 5);
		else
			errorprintf("minishell: cd: HOME not set\n", &minilst->cmdstatus);
	}
	else if (!strcmp(str, "-"))
	{
		i = getposinlst(minilst->envp, "OLDPWD") + 1;
		if (i != 0)
		{
			s = ft_strdup(getlineinenv(minilst->envp, i) + 7);
			ft_putstr_fd(s, fileout);
		}
		else
			errorprintf("minishell: cd: OLDPWD not set\n", &minilst->cmdstatus);
	}
	else
		s = comparse(str);
	return (s);
}
