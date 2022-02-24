#include "../../minishell.h"

int num_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}
