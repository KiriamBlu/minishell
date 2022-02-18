/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:12:21 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/18 16:41:52 by jsanfeli         ###   ########.fr       */
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

int getvariable(char *add, t_minib *minilst)
{
	char *tmp;
	char *aux;
	char *eaux;
	char *baux;
	char *caux;
	int i;
	
	i = 1;
	if(!ft_strchr(add, '='))
		return(minilst->envindex + 1);
	tmp = ft_strdup(ft_strchr(add, '='));
	aux = ft_substr(add, 0 , ft_strlen(add) - ft_strlen(tmp));
	eaux = ft_strdup(getlineinenv(minilst->envp, i));
	baux = ft_strdup(ft_strchr(eaux, '='));
	caux = ft_substr(eaux, 0 , ft_strlen(eaux) - ft_strlen(baux));
	while(strcmp(caux, aux) != 0 && i <= minilst->envindex)
	{
		free(eaux);
		free(baux);
		free(caux);
		eaux = ft_strdup(getlineinenv(minilst->envp, i));
		baux = ft_strdup(ft_strchr(eaux, '='));
		caux = ft_substr(eaux, 0 , ft_strlen(eaux) - ft_strlen(baux));
		i++;
	}
	free(eaux);
	free(baux);
	free(caux);
	return(i);
}
