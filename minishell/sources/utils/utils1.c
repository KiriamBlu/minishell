/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:12:21 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/27 16:56:05 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	printlist(t_list *list, int fileout)
{
	int	i;
	int	j;

	i = 0;
	j = ft_lstsize(list);
	if (j == 0)
		return ;
	while (i < j)
	{
		ft_putstr_fd((char *)list->content, fileout);
		ft_putchar_fd('\n', fileout);
		list = list->next;
		i++;
	}
}

void	printlistexp(t_list *list, int fileout)
{
	int	i;
	int	j;

	i = 0;
	j = ft_lstsize(list);
	while (i < j)
	{
		ft_putstr_fd("declare -x ", fileout);
		ft_putstr_fd((char *)list->content, fileout);
		ft_putchar_fd('\n', fileout);
		list = list->next;
		i++;
	}
}

t_list	*createarraylst(char **array)
{
	int		i;
	t_list	*aux;

	aux = NULL;
	if (array[0])
		aux = ft_lstnew(ft_strdup(array[0]));
	else
		return (NULL);
	i = 1;
	while (array[i])
	{
		ft_lstadd_back(&aux, ft_lstnew(ft_strdup(array[i])));
		i++;
	}
	return (aux);
}

char	**createlstarray(t_list *lst, int index)
{
	int		i;
	int		j;
	char	**aux;

	j = index;
	aux = ft_calloc(sizeof(char *), j + 1);
	i = 0;
	while (i < index)
	{
		aux[i] = NULL;
		aux[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	return (aux);
}

int	getvariable(char *add, t_list *list)
{
	char	*aux;
	char	*caux;
	void	*kk;
	int		listsize;
	int		i;

	i = 1;
	listsize = ft_lstsize(list);
	if (!ft_strchr(add, '='))
		return (listsize + 1);
	kk = list;
	aux = getnamevariable(add);
	caux = getnamevariable(list->content);
	while (ft_strcmp(caux, aux) != 0 && i < listsize)
	{
		free(caux);
		list = list->next;
		caux = getnamevariable(list->content);
		i++;
	}
	free(caux);
	free(aux);
	list = kk;
	return (i);
}
