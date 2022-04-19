
#include "../../minishell.h"

int checkforecho(char *cmd, char *arg)
{
	int i;
	int j;

	if (strcmp(cmd, "echo") != 0)
		return (0);
	j = -1;
	i = 0;
	while(arg[++j] == ' ')
		;
	while(arg[j])
	{
		if (arg[j] == '-' && arg[j + 1] == 'n')
		{
			j += 1;
			i = 1;
		}
		else if(arg[j] != '"' && arg[j] != '\'')
			printf("%c", arg[j]);
		j++;
	}
	if(i != 1)
		printf("\n");
	return (1);
}