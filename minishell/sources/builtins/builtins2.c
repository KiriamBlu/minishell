
#include "../../minishell.h"

char *argsdone(char *arg)
{
	int	a;
	char *argsdone;
	
	a = 0;
	while (arg[a])
	{
		if(arg[a] == '\'')
			while(arg[++a] != '\'')
				;
		if (arg[a] == '"')
			while(arg[++a] != '"')
				;
		if (arg[a] == '>' || arg[a] == '<')
		{
			while(arg[a - 1] == ' ')
				a--;
			break ;
		}
		a++;
	}
	argsdone = ft_substr(arg, 0, a);
	//system("leaks minishell");
	return (argsdone);
}

int checkforecho(char *cmd, char *arg, int fileout, int *status)
{
	int i;
	int j;
	char *print;

	if (ft_strcmp(cmd, "echo") != 0)
		return (0);
	print = argsdone(arg);
	j = -1;
	i = 0;
	while(print[++j] == ' ')
		;
	while(print[j])
	{
		if (print[j] == '-' && print[j + 1] == 'n')
		{
			j += 1;
			i = 1;
		}
		else if(print[j] != '"' && print[j] != '\'')
			ft_putchar_fd(print[j], fileout);
		j++;
	}
	if(i != 1)
		ft_putchar_fd('\n', fileout);
	free(print);
	*status = 0;
	return (1);
}