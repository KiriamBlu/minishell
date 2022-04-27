
#include "../../minishell.h"

char	**ft_prepare(char *line)
{
	char	**cmd;

	if (count_c(line, '|') > 0)
	{
		cmd = ft_splitmod(line, '|');
		return (cmd);
	}
	else
	{
		cmd = malloc(sizeof(char **) * 1);
		cmd[0] = ft_strdup(line);
	}
	cmd[1] = NULL;
	return (cmd);
}

/*int openfilesheredoc(char *line, int i, int *filein)
{
	int j;
	int l;
	char *aux;

	j = i;
	l = 0;
	while(line[++j] == ' ' && line[j])
		;	
	while(line[j] != ' ' && line[j])
	{
		if(line[j] == '>' || line[j] == '<')
			return(-1);
		j++;
		l++;
	}
	aux = malloc(sizeof(char) * l + 1);
	j = 0;
	while(line[++i] == ' ' && line[i])
		;	
	while(line[i] != ' ' && line[i])
	{
		aux[j] = line[i];
		j++;
		i++;
	}
	i -= 1;
	if (*fileout != STDOUT_FILENO)
		close(*fileout);
	
	free(aux);
	return(i);
}
*/
int openfilesindirect(char *line, int i, int *filein)
{
	int j;
	int l;
	char *aux;

	j = i;
	l = 0;
	/*if(line[i + 1] == '<')
	{
		i = openfilesheredoc(line, i + 1, fileinss);
		return(i);
	}*/
	while(line[++j] == ' ')
		;
	while(line[j] != ' ')
	{
		if(line[j] == '>' || line[j] == '<')
			return(-1);
		l++;
		j++;
	}
	aux = malloc(sizeof(char) * l + 1);
	j = 0;
	while(line[++i] == ' ' && line[i])
		;
	while(line[i] != ' ' && line[i])
	{
		aux[j] = line[i];
		j++;
		i++;
	}
	i -= 1;
	if (*filein != STDIN_FILENO)
		close(*filein);
	*filein = open(aux,  O_RDONLY, 0777);
	free(aux);
	return(i);
}

int openfilesappend(char *line, int i, int *fileout)
{
	int j;
	int l;
	char *aux;

	j = i;
	l = 0;
	while(line[++j] == ' ' && line[j])
		;	
	while(line[j] != ' ' && line[j])
	{
		if(line[j] == '>' || line[j] == '<')
			return(-1);
		j++;
		l++;
	}
	aux = malloc(sizeof(char) * l + 1);
	j = 0;
	while(line[++i] == ' ' && line[i])
		;	
	while(line[i] != ' ' && line[i])
	{
		aux[j] = line[i];
		j++;
		i++;
	}
	i -= 1;
	if (*fileout != STDOUT_FILENO)
		close(*fileout);
	*fileout = open(aux, O_WRONLY | O_CREAT | O_APPEND, 0666);
	free(aux);
	return(i);
}

int openfilesredirect(char *line, int i, int *fileout)
{
	int j;
	int l;
	char *aux;

	j = i;
	if(line[i + 1] == '>')
	{
		i = openfilesappend(line, i + 1, fileout);
		return(i);
	}
	l = 0;
	while(line[++j] == ' ' && line[j])
		;	
	while(line[j] != ' ' && line[j])
	{
		if(line[j] == '>' || line[j] == '<')
			return(-1);
		j++;
		l++;
	}
	aux = malloc(sizeof(char) * j + 1);
	j = 0;
	while(line[++i] == ' ' && line[i])
		;
	while(line[i] != ' ' && line[i])
	{
		aux[j] = line[i];
		j++;
		i++;
	}
	i -= 1;
	if (*fileout != STDOUT_FILENO)
		close(*fileout);
	*fileout = open(aux, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	free(aux);
	return(i);
}

int checkforredirect(char *line, int *filein, int *fileout)
{
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] == '"')
			while(line[++i] != '"')
				;
		if(line[i] == '\'')
			while(line[++i] != '\'')
				;
		if(line[i] == '>')
			i = openfilesredirect(line, i, fileout);
		if(line[i] == '<')
			i = openfilesindirect(line, i, filein);
		if (i == -1)
		{
			printf("Error unespected token\n");
			return(-1);
		}
		i++;
	}
	return(0);
}

int	morfeo(t_cmds *com, char **line)
{
	int		i;
	char	**aux;
	int		j;

	i = 0;
	while (line[i])
	{
		j = 0;
		com[i].filein = STDIN_FILENO;
		com[i].fileout = STDOUT_FILENO;
		aux = ft_split(line[i], ' ');
		if(aux[0])
		{	
			com[i].cmd = ft_strdup(aux[0]);
			freemat(aux);
			j = ft_strlen(com[i].cmd);
			com[i].args = ft_substr(line[i], j + 1, ft_strlen(line[i]));
			if (checkforredirect(line[i], &com[i].filein, &com[i].fileout) == -1)
				return(-1);
		}
		i++;
	}
	return(0);
}

int countpipe(char *expanded)
{
	int i;
	int k;
	
	i = 0;
	k = 0;
	while(expanded[i])
	{
		if(expanded[i] == '|')
			k++;
		if (expanded[i] == '\'')
			while(expanded[++i] != '\'')
				;
		if (expanded[i] == '"')
			while(expanded[++i] != '"')
				;
		i++;
	}
	return(k + 1);
}

char **lexer(char *expanded)
{
	int i;
	int a;
	int numcom;
	int status;
	char **comands;

	numcom = countpipe(expanded);
	comands = malloc(sizeof(char *) * numcom + 1);
	i = 0;
	a = 0;
	status = 0;
	while(numcom > 0)
	{
		while(expanded[i] != '|' && expanded[i])
		{
			if (expanded[i] == '\'')
				while(expanded[++i] != '\'')
					;
			if (expanded[i] == '"')
				while(expanded[++i] != '"')
					;
			i++;
		}
		comands[status] = ft_substr(expanded, a, i - a);
		i += 1;
		a = i;
		status++;
		numcom--;
	}
	comands[status] = 0;
	return(comands);
}
