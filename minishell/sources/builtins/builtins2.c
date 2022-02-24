
#include "../../minishell.h"

void checkforecho(char **line, t_minib *minilst)
{
	int i;
	int j;

	if (strcmp(line[0], "echo") != 0)
		return ;
	j = 0;
	i = 0;
	while(line[++j])
	{
		if (strcmp(line[j], "-n") == 0)
			i = 1;
		else
		{
			printf("%s", line[j]);
		}
	}
	if(i != 1)
		printf("\n");
}