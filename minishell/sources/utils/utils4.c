/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:43:16 by jporta            #+#    #+#             */
/*   Updated: 2022/05/23 20:04:08 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void errorprintf(char *str, int *status)
{
	printf("%s", str);
	*status = 1;
}

int lentmp(char *add)
{
	int j;
	int l;

	j = 0;
	l = 0;
	while(add[j])
	{
		if(add[j] == '"')
			while(add[++j] != '"' && add[j])
				l++;
		else if(add[j] == '\'')
			while(add[++j] != '\'' && add[j])
				l++;
		else
			l++;
		j++;
	}
	return(l);
}

char *comparse(char *add)
{
	int j;
	char *tmp;
	int	l;

	j = 0;
	tmp = ft_calloc(sizeof(char), lentmp(add) + 1);
	l = 0;
	while(add[j])
	{
		if(add[j] == '"' || add[j] == '\'')
		{
			if(add[j] == '"')
			{
				j++;
				while(add[j] != '"' && add[j])
					tmp[l++] = add[j++];
			}
			else if(add[j] == '\'')
			{
				j++;
				while(add[j] != '\'' && add[j])
					tmp[l++] = add[j++];
			}
		}
		else
		{
			tmp[l] = add[j];
			l++;
		}
		j++;
	}
	return(tmp);
}

int checkforspaces(char *line)
{
	int i;

	i = -1;
	while(line[++i])
		if(line[i] != ' ')
			return(1);
	return(0);
}

int checkinout(t_minib *minilst)
{
	int i;

	i = 0;
	while(i < minilst->cmdnum)
	{
		if(minilst->cmds[i].filein == -1 || minilst->cmds[i].fileout == -1)
		{
			printf("Not valid file\n");
			return (-1);
		}
		i++;
	}
	return(0);
}