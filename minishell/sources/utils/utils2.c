/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:28:24 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/17 18:04:18 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*fuckeveryting(t_list *list)
{
	void *kk;

	kk = list->next;
	free(list->content);
	free(list);
	return(kk);
}