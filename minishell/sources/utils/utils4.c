#include "../../minishell.h"


void errorprintf(char *str, int *status)
{
	printf("%s", str);
	*status = 1;
}

int lentmp(char *add)
{
	int j;
	int l;

	j = 0;
	l = 0;
	while(add[j])
	{
		if(add[j] == '"')
			while(add[++j] != '"')
				l++;
		else if(add[j] == '\'')
			while(add[++j] != '\'')
				l++;
		else
			l++;
		j++;
	}
	return(l);
}

char *comparse(char *add)
{
	int j;
	char *tmp;
	int	l;

	j = 0;
	tmp = ft_calloc(sizeof(char), lentmp(add) + 1);
	l = 0;
	while(add[j])
	{
		if(add[j] == '"' || add[j] == '\'')
		{
			if(add[j] == '"')
			{
				j++;
				while(add[j] != '"')
					tmp[l++] = add[j++];
			}
			else if(add[j] == '\'')
			{
				j++;
				while(add[j] != '\'')
					tmp[l++] = add[j++];
			}
		}
		else
		{
			tmp[l] = add[j];
			l++;
		}
		j++;
	}
	return(tmp);
}