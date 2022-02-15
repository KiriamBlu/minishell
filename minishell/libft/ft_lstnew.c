/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:33:56 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/15 17:26:12 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*l;

	l = NULL;
	l = malloc(sizeof(t_list));
	if (!l)
		return (NULL);
	l->content = content;
	l->next = 0;
	return (l);
}
