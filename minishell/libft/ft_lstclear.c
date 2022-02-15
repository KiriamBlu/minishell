/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:33:56 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/15 16:25:20 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list *lst, void (*del)(void*))
{
	t_list	*aux;

	if (!lst || !del)
		return ;
	while (lst)
	{
		aux = lst->next;
		ft_lstdelone(lst, del);
		lst = aux;
	}
}
