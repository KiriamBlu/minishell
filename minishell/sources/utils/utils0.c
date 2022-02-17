/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:12:21 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/17 18:10:43 by jsanfeli         ###   ########.fr       */
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

void delpos(t_list **list, int pos)
{
	int i;
	t_list *aux;

	i = 1;
	if(pos == 1)
	{
		*list = fuckeveryting(*list);
		return ;
	}
	while(++i < pos)
		*list = (*list)->next;
	aux = (*list)->next;
	(*list)->next = (*list)->next->next;
	aux->next = NULL;
	free(aux->content);
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

void	freeeverything(t_minib *minilst)
{
	ft_lstclear(minilst->envp, free);
	ft_lstclear(minilst->exp, free);
	free(minilst->pwd);
}
