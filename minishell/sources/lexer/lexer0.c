
#include "../../minishell.h"

int		countpipe(char *expanded);
char	*checkforredirect(char *line, int *filein, int *fileout);
int		openfilesredirect(char *line, int i, int *fileout);
int		openfilesappend(char *line, int i, int *fileout);
int		openfilesindirect(char *line, int i, int *filein);
int		openfilesheredoc(char *line, int i, int *filein);

/*WORKS BY DOING A SIMPLE READING AND APPLAYING THE SAME RULES OF THE EXPANDER BUT ON THIS CASE IT PUTS EACH CMD INT TO A POINTER OF A MATRIX*/

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

/*PREPS THE STRUCTURE OF CMDS AND OPENS THE FILES NECESARY*/

int	morfeo(t_cmds *com, char **line)
{
	int		i;
	char	**aux;
	char	*tmp;
	int		j;

	i = 0;
	while (line[i])
	{
		j = 0;
		com[i].filein = STDIN_FILENO; //SETS BASIC INPUT FOR THE CMD
		com[i].fileout = STDOUT_FILENO; //SETS BASIC OUTPUT FOR THE CMD
		com[i].cmd = NULL;
		com[i].args = NULL;
		tmp = checkforredirect(line[i], &com[i].filein, &com[i].fileout); //CHANGES THE INPUT OR OUTPUT IF NEEDED AND REMOVES REDDIRECTIOS INDIRECTONS APPENDS AND HERE DOCS
		if(tmp == NULL)
			return(-1);
		aux = ft_split(tmp, ' ');
		if(aux[0])
		{
			com[i].cmd = ft_strdup(aux[0]); //GETS THE CMD
			freemat(aux);
			while(tmp[j++] == ' ');
			j += ft_strlen(com[i].cmd);
			com[i].args = ft_substr(tmp, j, ft_strlen(tmp)); // GETS THE ARGS 
		}
		free(tmp);
		i++;
	}
	return(0);
}


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

char *gettmp(int i, char *line)
{
	int a;
	int j;
	char *tmp;

	a = i + 1;
	while (line[a] == ' ')
		a++;
	j = a;
	while (line[a] != ' ' && line[a])
		a++;
	tmp = ft_calloc(sizeof(char), (a - j) + 1);
	a = j;
	j = 0;
	while(line[a] != ' ' && line[a])
	{
		if(line[a] == '"')
		{
			a++;
			while(line[a] != '"' && line[a])
				tmp[j++] = line[a++];
		}
		else if(line[a] == '\'')
		{
			a++;
			while(line[a] != '\'' && line[a])
				tmp[j++] = line[a++];
		}
		else
			tmp[j] = line[a];
		j++;
		a++;
	}
	return(tmp);
}

int openfilesheredoc(char *line, int i, int *filein)
{
	int a;
	char *tmp;
	char *str;

	a = i + 1;
	while (line[a] == ' ' && line[a])
		a++;
	if(line[a] == '>' || line[a] == '<')
		return(-1);
	while (line[a] != ' ' && line[a])
		a++;
	tmp = gettmp(i, line);
	str = NULL;
	*filein = open(".hide", O_RDWR | O_CREAT | O_TRUNC, 0666);
	while(1)
	{
		str = readline("> ");
		if(!str)
			break;
		if (ft_strcmp(str, tmp) == 0)
		{
			free(str);
			break;
		}
		ft_putstr_fd(str, *filein);
		ft_putstr_fd("\n", *filein);
		free(str);
	}
	free(tmp);
	close(*filein);
	*filein = open(".hide", O_RDWR, 0666);
	return(a);
}

int openfilesindirect(char *line, int i, int *filein)
{
	int j;
	int l;
	char *aux;

	j = i;
	l = 0;
	if(line[i + 1] == '<')
	{
		i = openfilesheredoc(line, i + 1, filein);
		return(i);
	}
	while(line[++j] == ' ');
	while(line[j] != ' ')
	{
		if(line[j] == '>' || line[j] == '<')
			return(-1);
		l++;
		j++;
	}
	aux = ft_calloc(sizeof(char), j + 1);
	j = 0;
	while(line[++i] == ' ' && line[i]);
	while(line[i] != ' ' && line[i])
	{
		aux[j] = line[i];
		j++;
		i++;
	}
	if (*filein != STDIN_FILENO)
		close(*filein);
	*filein = open(aux,  O_RDONLY, 0666);
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
	while(line[++j] == ' ' && line[j]);	
	while(line[j] != ' ' && line[j])
	{
		if(line[j] == '>' || line[j] == '<')
			return(-1);
		j++;
		l++;
	}
	aux = ft_calloc(sizeof(char), j + 1);
	j = 0;
	while(line[++i] == ' ' && line[i]);	
	while(line[i] != ' ' && line[i])
	{
		aux[j] = line[i];
		j++;
		i++;
	}
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
	while(line[++j] == ' ' && line[j]);	
	while(line[j] != ' ' && line[j])
	{
		if(line[j] == '>' || line[j] == '<')
			return(-1);
		j++;
		l++;
	}
	aux = ft_calloc(sizeof(char), j + 1);
	j = 0;
	while(line[++i] == ' ' && line[i]);
	while(line[i] != ' ' && line[i])
	{
		aux[j] = line[i];
		j++;
		i++;
	}
	if (*fileout != STDOUT_FILENO)
		close(*fileout);
	*fileout = open(aux, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	free(aux);
	return(i);
}

char *checkforredirect(char *line, int *filein, int *fileout)
{
	int i;
	int l;
	char *tmp;
	char *aux;

	i = 0;
	l = 0;
	tmp = ft_strdup(line);
	while(tmp[i])
	{
		if(tmp[i] == '"')
			while(tmp[++i] != '"')
				;
		if(tmp[i] == '\'')  
			while(tmp[++i] != '\'')
				;
		if(tmp[i] == '<' || tmp[i] == '>')
		{
			if(tmp[i] == '>')
				l = openfilesredirect(tmp, i, fileout);
			if(tmp[i] == '<')
				l = openfilesindirect(tmp, i, filein);
			aux = ft_strdup(tmp);
			free(tmp);
			tmp = ft_substr(aux, 0, i);
			tmp = freezerjoin(tmp, ft_substr(aux, l, ft_strlen(aux)));
			free(aux);
		}
		if (l == -1)
		{
			if(tmp)
				free(tmp);
			printf("Error unespected token\n");
			return(NULL);
		}
		i++;
	}
	return(tmp);
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
