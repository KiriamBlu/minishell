
#include "../minishell.h"

void checkenvp(t_minib *minilst)
{
	char *tmp;
	char *aux;
	char *auxi;
	int j;

	if(getposinlst(minilst->envp, "PWD") == -1)
	{
		tmp = ft_strjoin("PWD=", minilst->pwd);
		ft_lstadd_back(&minilst->envp, ft_lstnew(ft_strdup(tmp)));
		free(tmp);
	}
	if(getposinlst(minilst->envp, "SHLVL") == -1)
	{
		tmp = ft_strjoin("SHLVL=", "1");
		minilst->shlvl = 1;
		ft_lstadd_back(&minilst->envp, ft_lstnew(ft_strdup(tmp)));
		minilst->shlvl = 1;
		free(tmp);
	}
	else
	{
		j = getposinlst(minilst->envp, "SHLVL");
		aux = ft_strdup(getlineinenv(minilst->envp, j + 1));
		auxi = getnamevariable(aux);
		tmp = ft_substr(aux, ft_strlen(auxi) + 1, ft_strlen(aux));
		free(aux);
		free(auxi);
		minilst->shlvl = ft_atoi(tmp) + 1;
		free(tmp);
		aux = ft_itoa(minilst->shlvl);
		tmp = ft_strjoin("SHLVL=", aux);
		putinpos(&minilst->envp, j + 1, ft_strdup(tmp));
		delpos(&minilst->envp, j);
		free(aux);
		free(tmp);
	}
	if(getposinlst(minilst->envp, "_") == -1)
	{
		tmp = ft_strjoin("_=", "/usr/bin/env");
		ft_lstadd_back(&minilst->envp, ft_lstnew(ft_strdup(tmp)));
		free(tmp);
	}
}

void prepbasics(t_minib *minilst, char **envp)
{
	int i;
	char **aux;
	char **tmp;

	minilst->pwd = getcwd(NULL, 0);
	i = 0;
	minilst->envp = createarraylst(envp);
	checkenvp(minilst);
	tmp = createlstarray(minilst->envp, ft_lstsize(minilst->envp));
	while(tmp[i])
		i++;
	aux = getdonexp(tmp, i);
	freemat(tmp);
	minilst->exp = createarraylst(aux);
	minilst->cmdstatus = 0;
	freemat(aux);
}

int	prepline(char *line, t_minib *minilst)
{
	int i;
	char	**newline;
	char	*expanded;

	i = 0;
	expanded = expander(line, minilst); //AÑADIR $? A LAS EXPANSIONES
	newline = lexer(expanded);
	minilst->cmds = malloc(sizeof(t_cmds) * num_matrix(newline));
	minilst->cmdnum = num_matrix(newline);
	i = morfeo(minilst->cmds, newline);
	freemat(newline);
	free(expanded);
	return(i);
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

int checkinout(t_minib *minilst)
{
	int i;

	i = 0;
	while(i < minilst->cmdnum)
	{
		if(minilst->cmds[i].filein == -1 || minilst->cmds[i].fileout == -1)
		{
			printf("Not valid file\n");
			return (-1);
		}
		i++;
	}
	return(0);
}

void finish_ejecucion(t_minib *minilst, int i, int num)
{
	int k;

	k = 0;
	k += checkforexit(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
	k += checkforcd(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst, minilst->cmds[i].fileout);
	k += checkforenv(minilst->cmds[i].cmd, minilst->envp, minilst->cmds[i].fileout, &minilst->cmdstatus);
	k += checkforecho(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst->cmds[i].fileout, &minilst->cmdstatus);
	if (ft_strcmp(minilst->cmds[i].cmd, "pwd") == 0 || ft_strcmp(minilst->cmds[i].cmd, "PWD") == 0)
	{
		free(minilst->pwd);
		minilst->pwd = getcwd(NULL, 0);
		ft_putstr_fd(minilst->pwd, minilst->cmds[i].fileout);
		ft_putchar_fd('\n', minilst->cmds[i].fileout);
		k += 1;
	}
	k += checkforexport(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst, minilst->cmds[i].fileout);
	k += checkforunset(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
	if (ft_strcmp(minilst->cmds[i].cmd, "leaks") == 0)
	{
		k++;
		system("leaks minishell");
	}
	if (k == 0)
		executer(minilst, i, num);
}

void ejecucion(t_minib *minilst, int i, int num)
{
	int k;

	k = 0;
	k += checkforexit(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
	k += checkforcd(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst, minilst->cmds[i].fileout);
	k += checkforenv(minilst->cmds[i].cmd, minilst->envp, minilst->cmds[i].fileout, &minilst->cmdstatus);
	k += checkforecho(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst->cmds[i].fileout, &minilst->cmdstatus);
	if (ft_strcmp(minilst->cmds[i].cmd, "pwd") == 0)
	{
		free(minilst->pwd);
		minilst->pwd = getcwd(NULL, 0);
		ft_putstr_fd(minilst->pwd, minilst->cmds[i].fileout);
		ft_putchar_fd('\n', minilst->cmds[i].fileout);
		k += 1;
	}
	k += checkforexport(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst, minilst->cmds[i].fileout);
	k += checkforunset(minilst->cmds[i].cmd, minilst->cmds[i].args, minilst);
	if (ft_strcmp(minilst->cmds[i].cmd, "leaks") == 0)
	{
		k++;
		system("leaks minishell");
	}
	if (k == 0)
		executer(minilst, i, num);
	else
		exit(0);
}

void	checkeverything(char *line, t_minib *minilst)
{
	int i;
	int filein;
	int fileout;

	i = 0;
	if(prepline(line, minilst) == -1)
		return ;
	if (checkinout(minilst) == -1)
		return ;
	if (minilst->cmds[0].cmd && ft_strlen(minilst->cmds[0].cmd) != 0)
	{
		while(i < minilst->cmdnum)
		{
			fileout = dup(STDOUT_FILENO);
			filein = dup(STDIN_FILENO);
			if (minilst->cmdnum > 1)
			{
				while (i < minilst->cmdnum - 1)
				{
					simba(minilst, i);
					i++;
				}
				dup2(minilst->cmds[i].filein, STDIN_FILENO);
				dup2(minilst->cmds[i].fileout, STDOUT_FILENO);
				finish_ejecucion(minilst, i, 1);
			}
			else
			{
				dup2(minilst->cmds[i].filein, STDIN_FILENO);
				dup2(minilst->cmds[i].fileout, STDOUT_FILENO);
				finish_ejecucion(minilst, i, 1);
			}
			i++;
			dup2(fileout, STDOUT_FILENO);
			dup2(filein, STDIN_FILENO);
		}
	}
}

int main(int argc, const char **argv, char **envp)
{
	t_minib	minilst;
	char *line;
	char *promt;
	int		i;

	argv = NULL;
	if(argc != 1)
		exit(0);
	i = 0;
	prepbasics(&minilst, envp);
	minilst.promt = dopromt(&minilst);
	while(1)
	{
		inputsignal();
		promt = ft_strdup(minilst.promt);
		line = readline(promt);
		if(!line)
		{
			printf("exit\n");
			if (i > 0)
				freecmds(&minilst);
			exit(0);
		}
		if (ft_strlen(line) != 0 && checkforspaces(line) != 0 && line)
		{
			add_history(line);
			checkeverything(line, &minilst);
			i++;
		}
		freecmds(&minilst);
		free(line);
		free(promt);
	}
	free(minilst.promt);
	return 0;
}

//HOLA PORTAAAAA