#include "../../minishell.h"

int	count_c(char *str, char c)
{
	size_t	i;
	int		count;

	count = 0;
	i = 0;
	if (str[0] && str[0] != c)
		count++;
	while (i < ft_strlen(str))
	{
		if (str[i] == '"')
			while (str[++i] != '"' && str[i] != '\0')
				;
		else if (str[i] == '\'' && str[i] != '\0')
			while (str[++i] != '\'')
				;
		else if (str[i] == c && str[i + 1] && str[i + 1] != c)
			count ++;
		i++;
	}
	return (count);
}

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

char	*freezerjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1)
		return(ft_strdup(s2));
	if (!s2)
		return(ft_strdup(s1));
	i = 0;
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (*(s1 + i) != '\0')
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	j = 0;
	while (*(s2 + j) != '\0')
	{
		*(str + i + j) = *(s2 + j);
		j++;
	}
	free(s1);
	free(s2);
	return (str);
}

char  *dopromt(t_minib *minilst)
{
	char *aux;
	char *aux2;
	char *helps;
	int		i;

	i = minilst->shlvl;
	aux = ft_strjoin(SKULL, " ");
	aux2 = ft_strjoin(aux, GREEN_BOLD);
	free(aux);
	aux = ft_strjoin(aux2, "Escromito_v0.");
	free(aux2);
	helps =  ft_itoa(i);
	aux2 = ft_strjoin(aux, helps);
	free(aux);
	free(helps);
	aux = ft_strjoin(aux2, MAG_BOLD);
	free(aux2);
	aux2 = ft_strjoin(aux, "-$>");
	free(aux);
	return(aux2);
}











