/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:51:56 by jporta            #+#    #+#             */
/*   Updated: 2022/05/27 17:11:01 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	freemat(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
}

char	*getlineinenv(t_list *list, int i)
{
	int	j;

	j = 0;
	while (++j < i)
		list = list->next;
	return (list->content);
}

void	freeeverything(t_minib *minilst)
{
	
	ft_lstclear(minilst->envp, free);
	ft_lstclear(minilst->exp, free);
	freecmds(minilst);
	free(minilst->pwd);
}
