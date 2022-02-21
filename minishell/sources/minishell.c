
#include "../minishell.h"

void prepbasics(t_minib *minilst, char **envp)
{
	int i;
	char **aux;

	minilst->pwd = getcwd(NULL, 0);
	i = 0;
	while(envp[i])
		i++;
	aux = getdonexp(envp, i);
	minilst->envp = createarraylst(envp);
	minilst->exp = createarraylst(aux);
	minilst->envindex = i;
	minilst->expindex = i;
	freemat(aux);
}

void checkeverything(char *line, t_minib *minilst)
{
	char	**auxline;

	auxline = lexer(minilst->envp, line);
	checkforexit(auxline, minilst);
	checkforcd(auxline, minilst);
	checkforenv(auxline, minilst->envp);
	if (strcmp(auxline[0], "pwd") == 0)
	{
		free(minilst->pwd);
		minilst->pwd = getcwd(NULL, 0);
		printf("%s\n", minilst->pwd);
		freemat(auxline);
		return ;
	}
	checkforexport(auxline, minilst);
	checkforunset(auxline, minilst);
	freemat(auxline);
	return ;
}

int main(int argc, const char **argv, char **envp)
{
	t_minib	minilst;
	char *line;

	argv = NULL;
	if(argc != 1)
		exit(0);
	prepbasics(&minilst, envp);
	while(1)
	{
		line = readline("minishell> ");
		add_history(line);
		checkeverything(line, &minilst);
		free(line);
	}
	return 0;
}

//HOLA PORTAAAAA