/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:28:24 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/27 17:11:24 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*fuckeveryting(t_list *list)
{
	void	*kk;

	kk = list->next;
	list->next = NULL;
	free(list->content);
	free(list);
	return (kk);
}

int	getgoodpositionexp(t_list *list, char *add)
{
	int		i;
	int		j;
	char	*aux;
	char	*tmp;

	j = 0;
	i = ft_lstsize(list);
	aux = getnamevariable(add);
	while (j < i)
	{
		tmp = getnamevariable(list->content);
		if (ft_strcmp(aux, tmp) < 0)
		{
			free(aux);
			free(tmp);
			return (j);
		}
		free(tmp);
		list = list->next;
		j++;
	}
	free(aux);
	return (j);
}

char	*getnamevariable(char *add)
{
	int		i;
	char	*kk;

	i = 0;
	while (add[i] && add[i] != '=')
		i++;
	kk = ft_substr(add, 0, i);
	return (kk);
}

int	itsinenv(char *add, t_list *list)
{
	int		i;
	int		j;
	char	*str[2];
	void	*kk;

	j = -1;
	kk = list;
	i = ft_lstsize(list);
	str[1] = getnamevariable(add);
	while (++j < i)
	{
		str[0] = getnamevariable(list->content);
		if (!ft_strcmp(str[0], str[1]))
		{
			free(str[1]);
			free(str[0]);
			list = kk;
			return (-1);
		}
		free(str[0]);
		list = list->next;
	}
	free(str[1]);
	list = kk;
	return (1);
}

void	freecmds(t_minib *minilst)
{
	int	i;

	i = 0;
	if (minilst->cmdnum != 0)
	{
		while (i < minilst->cmdnum)
		{
			if (minilst->cmds[i].cmd)
				free(minilst->cmds[i].cmd);
			if (minilst->cmds[i].args)
				free(minilst->cmds[i].args);
			if (minilst->cmds[i].filein != STDIN_FILENO)
				close(minilst->cmds[i].filein);
			if (minilst->cmds[i].fileout != STDOUT_FILENO)
				close(minilst->cmds[i].fileout);
			i++;
		}
		free(minilst->cmds);
		unlink(".hide");
		minilst->cmdnum = 0;
	}
}
