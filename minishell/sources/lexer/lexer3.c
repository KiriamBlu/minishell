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
	int		l;
	char	*tmp;

	i = 0;
	l = 0;
	if (!line || ft_strlen(line) == 0)
			return (NULL);
	tmp = ft_strdup(line);
	while (tmp[i])
	{
		if (tmp[i] == '"')
			while (tmp[++i] != '"')
				;
		if (tmp[i] == '\'')
			while (tmp[++i] != '\'')
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
	char	*aux;
	int		l;

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
	aux = ft_strdup(tmp);
	free(tmp);
	tmp = ft_substr(aux, 0, i);
	tmp = freezerjoin(tmp, ft_substr(aux, l, ft_strlen(aux)));
	free(aux);
	return (tmp);
}

char	*gettmp(int i, char *line)
{
	int		a;
	int		l;
	char	*tmp;
	char	*aux;

	a = i + 1;
	while (line[a] == ' ')
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

char *fillline(char *line, int *i)
{
	int j;
	int l;
	char *aux;

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
	return(aux);
}

int	openfilesindirect(char *line, int i, int *filein)
{

	char	*aux;

	if (line[i + 1] == '<')
		return (openfilesheredoc(line, i + 1, filein));
	aux = fillline(line, &i);
	if (!aux)
		return(-1);
	if (*filein != STDIN_FILENO)
		close(*filein);
	*filein = open(aux, O_RDONLY, 0666);
	free(aux);
	return (i);
}

int		openfilesappend(char *line, int	i, int *fileout)
{
	char	*aux;

	aux = fillline(line, &i);
	if (!aux)
		return(-1);
	if (*fileout != STDOUT_FILENO)
		close(*fileout);
	*fileout = open(aux, O_WRONLY | O_CREAT | O_APPEND, 0666);
	free(aux);
	return (i);
}

int		openfilesredirect(char *line, int i, int *fileout)
{
	char	*aux;


	if (line[i + 1] == '>')
		return (openfilesappend(line, i + 1, fileout));
	aux = fillline(line, &i);
	if (!aux)
		return(-1);
	if (*fileout != STDOUT_FILENO)
		close(*fileout);
	*fileout = open(aux, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	free(aux);
	return (i);
}
