/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/18 17:07:34 by jsanfeli         ###   ########.fr       */
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


	i = getvariable(add, minilst);
	if(itsinenv(add, minilst->exp) != -1)
	{
		if(ft_strchr(add, '='))
		{
			putinpos(&minilst->envp, i, ft_strdup(add));
			putinpos(&minilst->exp, getgoodpositionexp(minilst->exp, add), ft_strdup(add));
		}
		else
			putinpos(&minilst->exp, getgoodpositionexp(minilst->exp, add), ft_strdup(add));
	}
	else
	{
		printf("kk\n");
	}
}

void checkforexport(char **line, t_minib *minilst)
{
	if (ft_strncmp(line[0], "export", ft_strlen(line[0])) != 0)
		return	;
	if(!line[1])
	{
		printlistexp(minilst->exp);
		return ;
	}
	getaddexp(line[1], minilst);
}

void checkforunset(char **line, t_minib *minilst)
{
	int i;
	int j;

	j = 1;
	if (ft_strncmp(line[0], "unset", ft_strlen(line[0])) != 0)
		return	;
	if(!line[1])
		return ;
	while(line[j])
	{
		i = getposinlst(minilst->envp, line[j]);
		if(i)
		{
			minilst->envindex--;
			delpos(&minilst->envp, i);
		}
		i = getposinlst(minilst->exp, line[j]);
		if(i)
		{
			minilst->expindex--;
			delpos(&minilst->exp, i);
		}
		j++;
	}
}
