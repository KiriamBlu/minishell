
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

void checkforredirect(char *line, int *filein, int *fileout)
{
	int i;
	int flag;
	int j;
	char *aux;

	i = 0;
	j = 0;
	flag = 0;
	while(line[i])
	{
		if(line[i] == '>' || line[i] == '<')
		{
			if(line[i] == '>')
				flag = 1;
			j = i;
			while(line[++j] == ' ')
				while(line[++j] != ' ')
					;
			aux = malloc(sizeof(char) * j + 1);
			j = 0;
			while(line[++i] == ' ')
				while(line[++i] != ' ')
				{
					aux[j] = line[i];
					j++;
				}
			if (flag == 1)
			{
				if (*fileout != STDOUT_FILENO)
					close(*fileout);
				*fileout = open(aux, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				printf("%d\n", *fileout);
			}
			else			{
				if (*filein != STDIN_FILENO)
					close(*filein);
				*filein = open(aux,  O_RDONLY, 0666);
				printf("%d\n", *filein);

			}
			free(aux);
		}
		i++;
	}
}

void	morfeo(t_cmds *com, char **line)
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
			checkforredirect(line[i], &com[i].filein, &com[i].fileout);
			freemat(aux);
			j = ft_strlen(com[i].cmd);
			com[i].args = ft_substr(line[i], j + 1, ft_strlen(line[i]));
		}
		i++;
	}
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
