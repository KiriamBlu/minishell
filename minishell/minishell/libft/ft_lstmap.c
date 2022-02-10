/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:33:56 by jsanfeli          #+#    #+#             */
/*   Updated: 2021/09/27 11:12:57 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*aux;
	t_list	*start;		

	if (!f)
		return (NULL);
	start = NULL;
	while (lst)
	{	
		aux = ft_lstnew((*f)(lst->content));
		if (!aux)
		{
			ft_lstclear(&start, (*del));
			return (NULL);
		}
		ft_lstadd_back(&start, aux);
		lst = lst->next;
	}	
	return (start);
}
