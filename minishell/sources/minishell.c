/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:00:23 by jporta            #+#    #+#             */
/*   Updated: 2022/05/27 18:20:16 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*shlvlcreator(t_minib *minilst, int j)
{
	char	*tmp;
	char	*aux;
	char	*auxi;

	aux = ft_strdup(getlineinenv(minilst->envp, j + 1));
	auxi = getnamevariable(aux);
	tmp = ft_substr(aux, ft_strlen(auxi) + 1, ft_strlen(aux));
	free(aux);
	free(auxi);
	minilst->shlvl = ft_atoi(tmp) + 1;
	free(tmp);
	aux = ft_itoa(minilst->shlvl);
	tmp = ft_strjoin("SHLVL=", aux);
	free(aux);
	return (tmp);
}

void	auxenvp(t_minib *minilst)
{
	char	*tmp;
	int		j;

	if (getposinlst(minilst->envp, "PWD") == -1)
	{
		tmp = ft_strjoin("PWD=", minilst->pwd);
		ft_lstadd_back(&minilst->envp, ft_lstnew(ft_strdup(tmp)));
		free(tmp);
	}
	else
	{
		j = getposinlst(minilst->envp, "SHLVL");
		tmp = shlvlcreator(minilst, j);
		putinpos(&minilst->envp, j + 1, ft_strdup(tmp));
		delpos(&minilst->envp, j);
		free(tmp);
	}
}

void	checkenvp(t_minib *minilst)
{
	char	*tmp;

	if (getposinlst(minilst->envp, "SHLVL") == -1)
	{
		tmp = ft_strjoin("SHLVL=", "1");
		minilst->shlvl = 1;
		ft_lstadd_back(&minilst->envp, ft_lstnew(ft_strdup(tmp)));
		minilst->shlvl = 1;
		free(tmp);
	}
	auxenvp(minilst);
	if (getposinlst(minilst->envp, "_") == -1)
	{
		tmp = ft_strjoin("_=", "/usr/bin/env");
		ft_lstadd_back(&minilst->envp, ft_lstnew(ft_strdup(tmp)));
		free(tmp);
	}
}

void	prepbasics(t_minib *minilst, char **envp)
{
	int		i;
	char	**aux;
	char	**tmp;

	minilst->pwd = getcwd(NULL, 0);
	i = 0;
	minilst->envp = createarraylst(envp);
	checkenvp(minilst);
	tmp = createlstarray(minilst->envp, ft_lstsize(minilst->envp));
	while (tmp[i])
		i++;
	aux = getdonexp(tmp, i);
	freemat(tmp);
	minilst->exp = createarraylst(aux);
	if (getposinlst(minilst->envp, "OLDPWD") == -1)
		putinpos(&minilst->exp,
			getgoodpositionexp(minilst->exp, "OLDPWD"), getaddedexp("OLDPWD"));
	minilst->cmdstatus = 0;
	freemat(aux);
}

int	prepline(char *line, t_minib *minilst)
{
	int		i;
	int		a;
	char	**newline;
	char	*expanded;

	i = 0;
	a = 1;
	expanded = ft_strdup(line);
	while (countdollars(expanded) > 0)
		expanded = expander(expanded, minilst, i, a);
	newline = lexer(expanded);
	minilst->cmds = malloc(sizeof(t_cmds) * num_matrix(newline));
	minilst->cmdnum = num_matrix(newline);
	while (i < minilst->cmdnum)
	{
		minilst->cmds[i].filein = STDIN_FILENO;
		minilst->cmds[i].fileout = STDOUT_FILENO;
		minilst->cmds[i].cmd = NULL;
		minilst->cmds[i].args = NULL;
		i++;
	}
	i = morfeo(minilst->cmds, newline);
	freemat(newline);
	free(expanded);
	return (i);
}
