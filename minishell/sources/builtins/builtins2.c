
#include "../../minishell.h"

void checkforecho(char *cmd, char *arg)
{
	int i;
	int j;

	if (strcmp(cmd, "echo") != 0)
		return ;
	j = -1;
	i = 0;
	while(arg[++j])
	{
		if (arg[j] == '-' && arg[j + 1] == 'n')
		{
			j += 1;
			i = 1;
		}
		else
		{
			printf("%c", arg[j]);
		}
	}
	if(i != 1)
		printf("\n");
}