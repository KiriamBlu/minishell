#include "../../minishell.h"

int num_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

char *getaddedexp(char *add)
{
	char *aux;
	char *tmp;
	char *ls;
	char *kk;
	char *name;

	name = getnamevariable(add);
	kk = ft_strjoin(name, "=");
	free(name);
	ls = ft_substr(add, ft_strlen(name) + 1, ft_strlen(add));
	tmp = ft_strjoin("\"", ls);
	aux = ft_strjoin(kk, tmp);
	free(tmp);
	free(kk);
	free(ls);
	tmp = ft_strjoin(aux, "\"");
	free(aux);
	return(tmp);
}