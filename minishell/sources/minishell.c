
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

char	*prepline(char *line, t_minib *minilst)
{
	char	**newline;
	int		i;
	char	*polla;

	polla = ft_prueba(line, minilst->envp);
	printf("%s\n", polla);
	/* newline = lexer(minilst->envp, line, minilst->lexer);
	i = 0;
	while (newline[i])
	{
		printf("%s\n", newline[i]);
		i++;
	}
	minilst->cmds = malloc(sizeof(t_cmds) * num_matrix(newline));
	minilst->cmdnum = num_matrix(newline);
	morfeo(minilst->cmds, newline);
	freemat(newline); */
	return(polla);
}

int checkforspaces(char *line)
{
	int i;

	i = -1;
	while(line[++i])
		if(line[i] != ' ')
			return(1);
	return(0);
}

void	checkeverything(char *line, t_minib *minilst)
{
	char	**auxline;
	char	*linea;
	int i;

	i = 0;
	prepline(line, minilst);
	while(i < minilst->cmdnum)
	{
		checkforexit(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
		checkforcd(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
		checkforenv(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst->envp);
		checkforecho(minilst->cmds[i].cmd, minilst->cmds[i].args);
		if (strcmp(minilst->cmds[i].cmd, "pwd") == 0)
		{
			free(minilst->pwd);
			minilst->pwd = getcwd(NULL, 0);
			printf("%s\n", minilst->pwd);
		}
		checkforexport(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
		checkforunset(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
		if (strcmp(minilst->cmds[i].cmd, "leaks") == 0)
			system("leaks minishell");
		i++;
	}
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
		inputsignal();
		line = readline("minishell> ");
		if(!line) //LIBERAR STRUCT
		{
			printf("exit\n");
			exit(0);
		}
		if (ft_strlen(line) != 0 && checkforspaces(line) != 0 && line)
		{
			add_history(line);
			checkeverything(line, &minilst); //ESTO ES TODO EL TEMA DE PARSEO + COMANDOS
		}
		freecmds(&minilst);
		//system("leaks minishell");
		free(line);
	}
	return 0;
}

//HOLA PORTAAAAA