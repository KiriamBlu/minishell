
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

void	morfeo(t_cmds *com, char **line)
{
	int		i;
	char	**aux;
	int		j;

	i = 0;
	while (line[i])
	{
		j = 0;
		aux = ft_split(line[i], ' ');
		com[i].cmd = ft_strdup(aux[0]);
		freemat(aux);
		while (line[i][j] == ' ')
			j++;
		while (line[i][j] != ' ' && line[i][j])
			j++;
		com[i].args = ft_substr(line[i], j + 1, ft_strlen(line[i]));
		i++;
	}
}
//"hola" "|" | pepe "|"
