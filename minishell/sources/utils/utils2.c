/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:28:24 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/21 22:09:01 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*fuckeveryting(t_list *list)
{
	void *kk;

	kk = list->next;
	free(list->content);
	free(list);
	return(kk);
}

int getgoodpositionexp(t_list *list, char *add)
{
	int i;
	int j;
	char *aux;
	char *tmp;

	j = 0;
	i = ft_lstsize(list);
	aux = getnamevariable(add);
	while(j < i)
	{
		tmp = getnamevariable(list->content);
		if(strcmp(aux, tmp) < 0)
		{
			free(aux);
			free(tmp);
			return(j);
		}
		free(tmp);
		list = list->next;
		j++;
	}
	free(aux);
	return(j);
}

char	*getnamevariable(char *add)
{
	int i;
	char *kk;

	i = 0;
	while(add[i] && add[i] != '=')
		i++;
	kk = ft_substr(add, 0, i);
	return(kk);
}

int		itsinenv(char *add, t_list *list)
{
	int i;
	int j;
	char *str;
	char *tmp;
	void *kk;

	j = 0;
	kk = list;
	i = ft_lstsize(list);
	tmp = getnamevariable(add);
	while(j < i)
	{
		str = getnamevariable(list->content);
		if(!strcmp(str, tmp))
		{
			free(tmp);
			free(str);
			list = kk;
			return(-1);
		}
		free(str);
		list = list->next;
		j++;
	}
	free(tmp);
	list = kk;
	return(1);
}

void	freeeverything(t_minib *minilst)
{
	ft_lstclear(minilst->envp, free);
	ft_lstclear(minilst->exp, free);
	free(minilst->pwd);
}
