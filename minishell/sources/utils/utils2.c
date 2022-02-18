/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:28:24 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/18 17:18:42 by jsanfeli         ###   ########.fr       */
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

	j = 1;
	i = ft_lstsize(list);
	while(j < i)
	{
		if(strcmp(add, list->content) < 0)
			return(j);
		list = list->next;
		j++;
	}
	return(i + 1);
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

	j = 0;
	i = ft_lstsize(list);
	tmp = getnamevariable(add);
	while(j < i)
	{
		str = getnamevariable(list->content);
		if(!strcmp(str, tmp))
		{
			free(tmp);
			return(-1);
		}
		free(str);
		list = list->next;
		j++;
	}
	free(tmp);
	return(1);
}