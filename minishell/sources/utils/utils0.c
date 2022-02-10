/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:12:21 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/10 20:12:11 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void freemat(char **mat)
{
	int i;

	i = -1;
	while(mat[++i])
		free(mat[i]);
	free(mat);
}

void putinpos(t_list *list, int pos, void *newcontent) //IF LEAKS HERE IN TMP
{
	int i;
	t_list *aux;
	t_list *tmp;

	i = 1;
	while(++i < pos)
		list = list->next;
	tmp = list->next;
	aux = ft_lstnew(newcontent);
	list->next = aux;
	aux->next = tmp;
}

void delpos(t_list *list, int pos)
{
	int i;
	t_list *aux;
	t_list *tmp;

	i = 1;
	while(++i < pos)
		list = list->next;
	aux = list->next;
	list->next = list->next->next;
	aux->next = NULL;
	free(aux);
}

int	getposinlst(t_list *list, char *line)	
{
	int i;
	int j;
	char *aux;

	j = ft_lstsize(list);
	aux = ft_strjoin(line, "=");
	i = 1;
	while(i < j)
	{
		if(!ft_strncmp(list->content, aux, ft_strlen(aux)))
		{
			free(aux);
			return(i);
		}
		list = list->next;
		i++;
	}
	free(aux);
	return(-1);
}

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
		printf("%s\n", list->content);
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
