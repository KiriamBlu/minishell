/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/24 13:05:58 by jsanfeli         ###   ########.fr       */
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
		aux[count] = ft_strdup(envp[k]);
	}
	return(aux);
}

void getaddexp(char *add, t_minib *minilst)
{
	char *tmp;
	char *aux;
	int i;

	i = getvariable(add, minilst->envp);
	if(itsinenv(add, minilst->exp) != -1)
	{
		if(ft_strchr(add, '='))
		{
			putinpos(&minilst->envp, ft_lstsize(minilst->envp), ft_strdup(add));
			putinpos(&minilst->exp, getgoodpositionexp(minilst->exp, add), ft_strdup(add));//PONER COMILLAS DESPUES DEL IGUAL
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
			putinpos(&minilst->exp, i, ft_strdup(add));
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

void checkforexport(char **line, t_minib *minilst)
{
	int i;

	i = 0;
	if (strcmp(line[0], "export") != 0)
		return	;
	if(!line[1])
	{
		printlistexp(minilst->exp);
		return ;
	}
	while(line[++i])
	{
		if(checkadd(line[i]) == -1)
		{
			printf("minishell: export: %s: not a valid identifier\n", line[1]);
			return;
		}
		getaddexp(line[i], minilst);
	}
}

void checkforunset(char **line, t_minib *minilst)
{
	int i;
	int j;

	j = 0;
	if (strcmp(line[0], "unset") != 0)
		return	;
	if(!line[1])
		return ;
	while(line[++j])
	{
		if(checkadd(line[j]) == -1)
		{
			printf("minishell: unset: %s: not a valid identifier\n", line[1]);
			return;
		}
		i = getposinlst(minilst->envp, line[j]);
		if(i != -1)
		{
			minilst->envindex--;
			delpos(&minilst->envp, i);
		}
		i = getposinlst(minilst->exp, line[j]);
		if(i != -1)
		{
			minilst->expindex--;
			delpos(&minilst->exp, i);
		}
	}
}
