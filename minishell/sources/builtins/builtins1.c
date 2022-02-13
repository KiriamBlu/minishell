/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:19:23 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/10 20:06:49 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **getdonexp(char **envp, int i)
{
	char	**aux;
	int		j;
	int		k;
	int		count;

	aux = malloc(sizeof(char *) * i);
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

/*char **getaddexp(char *add, t_minib *minilst)
{
	int		i;
	int		j;
	int		k;
	char	**aux;

	i = 0;
	while(minilst->exp[i])
		i++;
	aux = malloc(sizeof(char *) * (i + 1));
	j = 0;
	k = 0;
	while(j < (i + 1))
	{
		if (ft_strncmp(add, minilst->exp[k], ft_strlen(minilst->exp[k]) + 1) < 0)
		{
			aux[j] = ft_strdup(minilst->exp[k]);
			k++;
		}
		else
			aux[j] = ft_strjoin("declare -x ", add);
		j++;
	}
	freemat(minilst->exp);
	return(aux);
}*/

void checkforexport(char **line, t_minib *minilst)
{
	int	i;

	i = -1;
	if (ft_strcmp(line[0], "export") != 6)
		return	;
	if(!line[1])
	{
		printlist(minilst->exp);
		return ;
	}
	//minilst->exp = getaddexp(line[1], minilst);
}