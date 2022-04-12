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
	if (!s1 || !s2)
		return (NULL);
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
