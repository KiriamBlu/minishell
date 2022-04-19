
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

void	prepline(char *line, t_minib *minilst)
{
	char	**newline;
	char	*expanded;

	expanded = expander(line, minilst->envp);
	newline = lexer(expanded);;
	minilst->cmds = malloc(sizeof(t_cmds) * num_matrix(newline));
	minilst->cmdnum = num_matrix(newline);
	morfeo(minilst->cmds, newline);
	freemat(newline);
	free(expanded);
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
	int i;
	int k;

	i = 0;
	prepline(line, minilst);
	if(minilst->cmds[0].cmd && ft_strlen(minilst->cmds[0].cmd) != 0)
	{
		while(i < minilst->cmdnum)
		{
			k = 0;
			k += checkforexit(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
			k += checkforcd(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
			k += checkforenv(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst->envp);
			k += checkforecho(minilst->cmds[i].cmd, minilst->cmds[i].args);
			if (strcmp(minilst->cmds[i].cmd, "pwd") == 0)
			{
				free(minilst->pwd);
				minilst->pwd = getcwd(NULL, 0);
				printf("%s\n", minilst->pwd);
				k += 1;
			}
			k += checkforexport(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
			k += checkforunset(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
			if (strcmp(minilst->cmds[i].cmd, "leaks") == 0)
				system("leaks minishell");
			if (k == 0)
				executer(minilst, i);
			i++;
		}
	}
}

int main(int argc, const char **argv, char **envp)
{
	t_minib	minilst;
	char *line;
	int		i;

	argv = NULL;
	if(argc != 1)
		exit(0);
	i = 0;
	prepbasics(&minilst, envp);
	while(1)
	{
		inputsignal();
		line = readline("minishell> ");
		if(!line)
		{
			printf("exit\n");
			if (i > 0)
				freecmds(&minilst);
			//system("leaks minishell");
			exit(0);
		}
		if (ft_strlen(line) != 0 && checkforspaces(line) != 0 && line)
		{
			add_history(line);
			checkeverything(line, &minilst); //ESTO ES TODO EL TEMA DE PARSEO + COMANDOS
			i++;
		}
		freecmds(&minilst);
		//system("leaks minishell");
		free(line);
	}
	return 0;
}

//HOLA PORTAAAAA