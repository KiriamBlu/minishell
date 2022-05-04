#include "../../minishell.h"


void errorprintf(char *str, int *status)
{
	printf("%s", str);
	*status = 1;
}
