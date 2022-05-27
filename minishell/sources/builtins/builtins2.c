/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/04/29 00:02:07 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**getdonexp(char **envp, int i);
char	*do_real_arg(char *add);
void	getaddexp(char *add, t_minib *minilst);
void	getexported(char **args, t_minib *minilst);

int	checkforexport(char *cmd, char *arg, t_minib *minilst, int fileout)
{
	char	**args;

	if (!cmd || ft_strcmp(cmd, "export") != 0)
		return (0);
	if (checkarg(arg) == 1)
	{
		printlistexp(minilst->exp, fileout);
		minilst->cmdstatus = 0;
		return (1);
	}
	args = exportarg(arg);
	getexported(args, minilst);
	freemat(args);
	return (1);
}

void	getexported(char **args, t_minib *minilst)
{
	int		i;
	char	*tmp;

	i = -1;
	while (args[++i])
	{
		tmp = comparse(args[i]);
		if (checkadd(tmp) == -1)
		{
			printf("minishell: export: %s: not a valid identifier\n", tmp);
			minilst->cmdstatus = 1;
			return ;
		}
		getaddexp(tmp, minilst);
		free(tmp);
	}
	minilst->cmdstatus = 0;
}

char	**getdonexp(char **envp, int i)
{
	char	**aux;
	int		j;
	int		k;
	int		count;

	aux = ft_calloc(sizeof(char *), i + 1);
	k = -1;
	while (envp[++k])
	{
		count = 0;
		j = -1;
		while (envp[++j])
		{
			if (ft_strncmp(envp[k], envp[j], ft_strlen(envp[j]) + 1) > 0)
				count++;
		}
		aux[count] = getaddedexp(envp[k]);
	}
	return (aux);
}

void	editenv(char *add, t_minib *minilst, int i)
{
	char	*tmp;
	char	*aux;

	tmp = getnamevariable(add);
	aux = do_real_arg(add);
	if (itsinenv(add, minilst->envp) == -1 && ft_strchr(add, '='))
		delpos(&minilst->envp, i - 1);
	if (ft_strchr(add, '='))
		putinpos(&minilst->envp, i - 1, ft_strdup(aux));
	i = getposinlst(minilst->exp, tmp);
	if (itsinenv(add, minilst->envp) == -1 && ft_strchr(add, '='))
	{
		delpos(&minilst->exp, i);
		putinpos(&minilst->exp, i, getaddedexp(aux));
	}
	free(tmp);
	free(aux);
}

void	getaddexp(char *add, t_minib *minilst)
{
	char	*tmp;
	int		i;

	i = getvariable(add, minilst->envp);
	if (itsinenv(add, minilst->exp) != -1)
	{
		if (ft_strchr(add, '='))
		{
			tmp = do_real_arg(add);
			putinpos(&minilst->envp, ft_lstsize(minilst->envp), ft_strdup(tmp));
			putinpos(&minilst->exp, getgoodpositionexp(minilst->exp, add),
				getaddedexp(tmp));
			free(tmp);
		}
		else
			putinpos(&minilst->exp, getgoodpositionexp(minilst->exp, add),
				ft_strdup(add));
	}
	else
		editenv(add, minilst, i);
}
