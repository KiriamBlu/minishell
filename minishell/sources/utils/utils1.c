/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:12:21 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/21 22:08:13 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *getlineinenv(t_list *list, int i)	
{
	int j;

	j = 0;
	while(++j < i)
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
void	printlistexp(t_list *list)
{
	int i;
	int j;

	i = 0;
	j = ft_lstsize(list);
	while(i < j)
	{
		printf("declare -x ");
		printf("%s\n", (char *)list->content);
		list = list->next;
		i++;
	}
}

t_list *createarraylst(char **array)
{
	int i;
	t_list *aux;

	aux = NULL;
	i = 0;
	while(array[i])
	{
		ft_lstadd_back(&aux, ft_lstnew(ft_strdup(array[i])));
		i++;
	}
	return(aux);
}

char **createlstarray(t_list *lst, int index)
{
	int i;
	int j;
	char **aux;

	j = index;
	aux = malloc(sizeof(char *) * j);
	i = 0;
	while (i < index)
	{
		aux[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	return (aux);
}

int getvariable(char *add, t_list *list)
{
	char *aux;
	char *caux;
	void *kk;
	int	listsize;
	int i;
	
	i = 1;
	listsize = ft_lstsize(list);
	if(!ft_strchr(add, '='))
		return(listsize + 1);
	kk = list;
	aux = getnamevariable(add);
	caux = getnamevariable(list->content);
	while(strcmp(caux, aux) != 0 && i < listsize)
	{
		free(caux);
		list = list->next;
		caux = getnamevariable(list->content);
		i++;
	}
	free(caux);
	free(aux);
	list = kk;
	return(i);
}
