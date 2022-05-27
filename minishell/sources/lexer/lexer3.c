/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>           +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:27 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/04/19 23:17:42 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		openfilesredirect(char *line, int i, int *fileout);
int		openfilesappend(char *line, int i, int *fileout);
int		openfilesindirect(char *line, int i, int *filein);
int		openfilesheredoc(char *line, int i, int *filein);
char	*auxred(char *tmp, int i, int *filein, int *fileout);

char	*checkredirect(char *line, int *filein, int *fileout)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!line || ft_strlen(line) == 0)
		return (NULL);
	tmp = ft_strdup(line);
	while ((int)ft_strlen(tmp) > i && tmp[i])
	{
		if (tmp[i] == '"')
			while (tmp[++i] != '"' && tmp[i])
				;
		if (tmp[i] == '\'')
			while (tmp[++i] != '\'' && tmp[i])
				;
		if (tmp[i] == '<' || tmp[i] == '>')
			tmp = auxred(tmp, i, filein, fileout);
		if (!tmp || ft_strlen(tmp) == 0)
			return (NULL);
		i++;
	}
	return (tmp);
}

char	*auxred(char *tmp, int i, int *filein, int *fileout)
{
	char	*auxi;
	char	*help;
	int		l;

	auxi = NULL;
	if (tmp[i] == '>')
		l = openfilesredirect(tmp, i, fileout);
	if (tmp[i] == '<')
		l = openfilesindirect(tmp, i, filein);
	if (l == -1)
	{
		free(tmp);
		printf("Error unespected token\n");
		return (NULL);
	}
	auxi = ft_substr(tmp, 0, i);
	help = ft_substr(tmp, l, ft_strlen(tmp));
	auxi = freezerjoin(auxi, help);
	free(tmp);
	return (auxi);
}

char	*gettmp(int i, char *line)
{
	int		a;
	int		l;
	char	*tmp;
	char	*aux;

	a = i + 1;
	while (line[a] == ' ' && line[a])
		a++;
	if (line[a] == '>' || line[a] == '<' || !line[a])
		return (NULL);
	l = a;
	while (line[l] != ' ' && line[l])
		l++;
	tmp = ft_substr(line, a, (l - a));
	aux = comparse(tmp);
	free(tmp);
	return (aux);
}

int	ft_getlen(int i, char *line, int *filein)
{
	while (line[i] == ' ')
		i++;
	while (line[i] != ' ' && line[i])
		i++;
	close(*filein);
	*filein = open(".hide", O_RDWR, 0666);
	return (i);
}

char	*fillline(char *line, int *i)
{
	int		j;
	int		l;
	char	*aux;

	j = *i;
	l = *i;
	while (line[++j] == ' ' && line[j])
		;
	while (line[j] != ' ' && line[j])
		if (line[j] == '>' || line[j++] == '<')
			return (NULL);
	aux = ft_calloc(sizeof(char), j + 1);
	j = 0;
	while (line[++l] == ' ' && line[l])
		;
	while (line[l] != ' ' && line[l])
		aux[j++] = line[l++];
	*i = l;
	return (aux);
}
