/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:27 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/23 19:55:11 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		openfilesredirect(char *line, int i, int *fileout);
int		openfilesappend(char *line, int i, int *fileout);
int		openfilesindirect(char *line, int i, int *filein);
int		openfilesheredoc(char *line, int i, int *filein);

int	openfilesheredoc(char *line, int i, int	*filein)
{
	char	*tmp;
	char	*str;

	tmp = gettmp(i, line);
	if (tmp == NULL)
		return (-1);
	str = NULL;
	*filein = open(".hide", O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (ft_strcmp(str, tmp) == 0)
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, *filein);
		ft_putstr_fd("\n", *filein);
		free(str);
	}
	free(tmp);
	return (ft_getlen(i + 1, line, filein));
}

int	openfilesindirect(char *line, int i, int *filein)
{
	char	*aux;

	if (line[i + 1] == '<')
		return (openfilesheredoc(line, i + 1, filein));
	aux = fillline(line, &i);
	if (!aux)
		return (-1);
	if (*filein != STDIN_FILENO)
		close(*filein);
	*filein = open(aux, O_RDONLY, 0666);
	free(aux);
	return (i);
}

int	openfilesappend(char *line, int i, int *fileout)
{
	char	*aux;

	aux = fillline(line, &i);
	if (!aux)
		return (-1);
	if (*fileout != STDOUT_FILENO)
		close(*fileout);
	*fileout = open(aux, O_WRONLY | O_CREAT | O_APPEND, 0666);
	free(aux);
	return (i);
}

int	openfilesredirect(char *line, int i, int *fileout)
{
	char	*aux;

	if (line[i + 1] == '>')
		return (openfilesappend(line, i + 1, fileout));
	aux = fillline(line, &i);
	if (!aux)
		return (-1);
	if (*fileout != STDOUT_FILENO)
		close(*fileout);
	*fileout = open(aux, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	free(aux);
	return (i);
}
