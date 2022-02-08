/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:12:21 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/08 23:33:02 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	rebuild_pwd(void)
{
	char	*pwd;

	//pwd = getpwd(NULL, 0);
}

int	find_env(char *name, char **env)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strjoin(name, "=");
	while (env[i])
	{
		if (!ft_strncmp(env[i], aux, ft_strlen(aux)))
		{
			free(aux);
			return (i);
		}
		i++;
	}
	free(aux);
	return (-1);
}

void freemat(char **mat)
{
	int i;

	i = -1;
	while(mat[++i])
		free(mat[i]);
	free(mat);
}