/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:12:21 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/10 20:12:11 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *getlineinenv(t_list *list, int i)	
{
	int j;

	j = -1;
	while(++j < i - 1)
		list = list->next;
	return(list->content);
}

void	printlist(t_list *list)
{
	int i;
	int j;

	i = 0;
	j = ft_lstsize(list);
	while(i < j)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
		i++;
	}
}

t_list *createarraylst(char **array, int index)
{
	int i;
	t_list *aux;

	aux =  malloc(sizeof(t_list) * index);
	aux = ft_lstnew(ft_strdup(array[0]));
	i = 0;
	while(array[++i])
		ft_lstadd_back(&aux, ft_lstnew(ft_strdup(array[i])));
	return(aux);
}

char **createlstarray(t_list *lst, int index)
{
	int i;
	char **aux;

	aux = malloc(sizeof(char *) * index);
	i = 0;
	while (i < index)
	{
		aux[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	return (aux);
}