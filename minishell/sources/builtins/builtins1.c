/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/03/03 16:04:31 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **getdonexp(char **envp, int i)
{
	char	**aux;
	int		j;
	int		k;
	int		count;

	aux = ft_calloc(sizeof(char *), i + 1);
	k = -1;
	while(envp[++k])
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
	return(aux);
}

void getaddexp(char *add, t_minib *minilst)
{
	char *tmp;
	int i;

	i = getvariable(add, minilst->envp);
	if(itsinenv(add, minilst->exp) != -1)
	{
		if(ft_strchr(add, '='))
		{
			putinpos(&minilst->envp, ft_lstsize(minilst->envp), ft_strdup(add));
			putinpos(&minilst->exp, getgoodpositionexp(minilst->exp, add), getaddedexp(add));
		}
		else
			putinpos(&minilst->exp, getgoodpositionexp(minilst->exp, add), ft_strdup(add));
	}
	else
	{
		tmp = getnamevariable(add);
		if(itsinenv(add, minilst->envp) == -1 && ft_strchr(add, '='))
			delpos(&minilst->envp, i - 1);
		if(ft_strchr(add, '='))
			putinpos(&minilst->envp, i - 1, ft_strdup(add));
		i = getposinlst(minilst->exp, tmp);
		if(itsinenv(add, minilst->envp) == -1 && ft_strchr(add, '='))
		{
			delpos(&minilst->exp, i);
			putinpos(&minilst->exp, i, getaddedexp(add));
		}
		free(tmp);
	}
}

int checkadd(char *add)
{
	char *aux;
	int i;

	i = 0;
	if(add[0] == '=' || ft_isdigit(add[0]) == 1)
		return(-1);
	aux = getnamevariable(add);
	while(aux[i])
	{
		if(ft_isalnum(aux[i]) == 0 && aux[i] != '_')
		{
			free(aux);
			return(-1);
		}
		i++;
	}
	free(aux);
	return(0);
}

void checkforexport(char *cmd, char *arg, t_minib *minilst)
{
	int i;
	char **args;

	i = -1;
	if (strcmp(cmd, "export") != 0)
		return	;
	args = ft_split(arg, ' ');
	if(!args[0])
	{
		freemat(args);
		printlistexp(minilst->exp);
		return ;
	}
	while(args[++i])
	{
		if(checkadd(args[i]) == -1)
			printf("minishell: export: %s: not a valid identifier\n", args[1]);
		getaddexp(args[i], minilst);
	}
	freemat(args);
}

void checkforunset(char *cmd, char *arg, t_minib *minilst)
{
	int i;
	int j;
	char **args;

	j = -1;
	if (strcmp(cmd, "unset") != 0)
		return	;
	args = ft_split(arg, ' ');
	if(!args[0])
		return ;
	while(args[++j])
	{
		if(checkadd(args[j]) == -1)
			printf("minishell: unset: %s: not a valid identifier\n", args[1]);
		i = getposinlst(minilst->envp, args[j]);
		if(i != -1)
		{
			minilst->envindex--;
			delpos(&minilst->envp, i);
		}
		i = getposinlst(minilst->exp, args[j]);
		if(i != -1)
		{
			minilst->expindex--;
			delpos(&minilst->exp, i);
		}
	}
	freemat(args);
}
