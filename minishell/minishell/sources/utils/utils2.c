/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:28:24 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/15 19:26:31 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fuckeveryting(t_list *list)
{
	int i;

	i = 0;
	while(i < ft_lstsize(list) - 1)
	{
		free(list->content);
		list->content = ft_strdup(list->next->content);
		list = list->next;
		i++;
	}
	list->next = NULL;
	free(list->content);
	free(list);
}