
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

	newline = lexer(minilst->envp, line);
	minilst->cmds = malloc(sizeof(t_cmds) * num_matrix(newline));
	minilst->cmdnum = num_matrix(newline);
	morfeo(minilst->cmds, newline);
	freemat(newline);
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

	i = 0;
	if (ft_strlen(line) != 0 && checkforspaces(line) != 0)
	{
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
		freecmds(&minilst);
		//system("leaks minishell");
		free(line);
	}
	return 0;
}

//HOLA PORTAAAAA