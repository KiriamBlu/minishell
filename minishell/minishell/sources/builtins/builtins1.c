/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/15 19:14:41 by jsanfeli         ###   ########.fr       */
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
		aux[count] = ft_strjoin("declare -x ", envp[k]);
	}
	return(aux);
}

void getaddexp(char *add, t_minib *minilst)
{
	char *tmp;
	char *aux;
	int i;
		
	i = getvariable(add, minilst);
	if(i == minilst->envindex)
	{
		aux = ft_strchr(getlineinenv(minilst->envp, i), '=');
		tmp = ft_strdup(ft_strchr(add, '='));
		if (ft_strcmp(tmp, aux) == 0)
			return ;
		else
		{
			delpos(minilst->envp, i);
			putinpos(minilst->envp, i, ft_strdup(add));
		}
		free(tmp);
		free(aux);
	}
	/*else
	{

	}*/
}

void checkforexport(char **line, t_minib *minilst)
{
	int	i;

	i = -1;
	if (ft_strncmp(line[0], "export", ft_strlen(line[0])) != 0)
		return	;
	if(!line[1])
	{
		printlist(minilst->exp);
		return ;
	}
	getaddexp(line[1], minilst);
}